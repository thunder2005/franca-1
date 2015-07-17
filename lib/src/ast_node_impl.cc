/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "ast_node_impl.hh"

// local includes:
#include "entity_impl.hh"

// franca includes:
#include "franca/ast_node.hh"
#include "franca/ast_visitor.hh"

// std includes:
#include <cassert>

using namespace franca;

static bool split_fqn( const std::string &fqn, std::string &name, std::string &rest )
{
    assert(!fqn.empty());

    auto dot_pos = fqn.find('.');
    if ( dot_pos == std::string::npos ) {
        name = fqn;
        return false;
    } else {
        name = fqn.substr(0, dot_pos);
        rest = fqn.substr(dot_pos + 1);
        assert(!(name.empty() || rest.empty())); // FQN contains empty segments
        return true;
    }
}

std::shared_ptr<ast_node_impl_t> ast_node_impl_t::create_root()
{
    return std::make_shared<ast_node_impl_t>(private_ctr{});
}

std::shared_ptr<ast_node_impl_t> ast_node_impl_t::create( const std::string &name )
{
    return std::make_shared<ast_node_impl_t>(private_ctr{}, name);
}

std::shared_ptr<ast_node_impl_t>
        ast_node_impl_t::create( const std::string &name,
                                 const std::shared_ptr<ast_node_impl_t> &parent )
{
    auto node = ast_node_impl_t::create(name);
    node->rebase(parent);
    return node;
}

ast_node_impl_t::ast_node_impl_t( private_ctr )
{
}

ast_node_impl_t::ast_node_impl_t( private_ctr, const std::string &name )
    : m_name(name)
{
    assert(!m_name.empty());
}

ast_node_t ast_node_impl_t::interface() noexcept
{
    return ast_node_t(shared_from_this());
}

std::string ast_node_impl_t::fqn() const
{
    auto locked_parent = m_parent.lock();
    if ( locked_parent && !locked_parent->is_root() ) {
        return locked_parent->fqn() + "." + m_name;
    } else {
        return m_name;
    }
}

std::shared_ptr<ast_node_impl_t> ast_node_impl_t::parent() const
{
    return m_parent.lock();
}

bool ast_node_impl_t::has_parent() const
{
    return !m_parent.expired();
}

void ast_node_impl_t::bind_entity( const std::shared_ptr<entity_impl_t> &entity ) noexcept
{
    assert(!m_entity);
    assert(!entity->has_ast_node());
    m_entity = entity;
    m_entity->m_ast_node = shared_from_this();
}

void ast_node_impl_t::rebase( const std::shared_ptr<ast_node_impl_t> &new_parent )
{
    auto locked_parent = m_parent.lock();
    if ( locked_parent == new_parent )
        return;

    new_parent->m_children.insert({m_name, shared_from_this()});

    if ( locked_parent ) {
        locked_parent->m_children.erase(m_name);
    }

    m_parent = new_parent;
}

std::shared_ptr<ast_node_impl_t>
        ast_node_impl_t::subnode_at( const std::string &fqn, ast_flags_t flags ) noexcept
{
    std::string name, rest;
    const bool has_rest = split_fqn(fqn, name, rest);

    auto it = m_children.find(name);
    const bool is_subnode_found = (it != m_children.end());

    /* Simple case. FQN contains only a single identifier. */
    if ( !has_rest ) {
        if ( is_subnode_found ) {
            if ( flags.is_set(ast_flag_t::create_exclusive) ) {
                return nullptr; //  AST node already exists
            } else {
                const auto &subnode = it->second;
                if ( flags.is_set(ast_flag_t::free) && subnode->has_entity() ) {
                    return nullptr; // FQN is already used
                }
                return subnode;
            }
        } else {
            if ( flags.is_set(ast_flag_t::create) ) {
                return ast_node_impl_t::create(name, shared_from_this());
            } else {
                return nullptr; // AST node does not exist
            }
        }
    }

    /* If we are here, then FQN contains at least two identifiers. */

    if ( is_subnode_found ) {
        return it->second->subnode_at(rest, flags);
    } else {
        if ( flags.is_set(ast_flag_t::create_recursive) ) {
            auto subnode = ast_node_impl_t::create(name, shared_from_this());
            return subnode->subnode_at(rest, flags);
        } else {
            return nullptr; // Some nodes for the given FQN do not exist
        }
    }
}

void ast_node_impl_t::accept_visitor( ast_visitor_t &visitor )
{
    if ( m_entity ) {
        m_entity->accept_visitor(visitor);
    } else {
        visitor.visit(interface());
    }
}
