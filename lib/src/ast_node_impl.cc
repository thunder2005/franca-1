/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "ast_node_impl.hh"

// local includes:
#include "parse_error.hh"

using namespace franca;

static bool split_fqn( const std::string &fqn, std::string &name, std::string &rest )
{
    if ( fqn.empty() )
        throw parse_error_t("FQN is empty");

    auto dot_pos = fqn.find('.');
    if ( dot_pos == std::string::npos ) {
        name = fqn;
        return false;
    } else {
        name = fqn.substr(0, dot_pos);
        rest = fqn.substr(dot_pos + 1);
        if ( name.empty() || rest.empty() )
            throw parse_error_t("FQN contains empty segments");
        return true;
    }
}

static void assert_name( const std::string &name )
{
    if ( name.empty() )
        throw parse_error_t("AST node name is empty");
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
    assert_name(m_name);
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
        ast_node_impl_t::subnode_at( const std::string &name )
{
    auto it = m_children.find(name);
    if ( it != m_children.end() ) {
        return it->second;
    } else {
        return ast_node_impl_t::create(name, shared_from_this());
    }
}

std::shared_ptr<ast_node_impl_t>
        ast_node_impl_t::subpath_at( const std::string &fqn )
{
    std::string name, rest;
    const bool has_rest = split_fqn(fqn, name, rest);

    // if fqn == name:
    if ( !has_rest )
        return subnode_at(name);

    auto it = m_children.find(name);
    if ( it != m_children.end() ) {
        return it->second->subpath_at(rest);
    } else {
        auto subnode = ast_node_impl_t::create(name, shared_from_this());
        return subnode->subpath_at(rest);
    }
}
