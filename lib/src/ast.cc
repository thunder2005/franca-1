/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "ast.hh"

// local includes:
#include "parser_impl.hh"
#include "log.hh"
#include "ast_node_impl.hh"
#include "entity/package_impl.hh"
#include "entity/type_collection_impl.hh"
#include "entity/integer_impl.hh"

// std includes:
#include <cassert>

using namespace franca;

static std::map<std::string, std::shared_ptr<entity::type_impl_t> >
        create_predefined_types()
{
    using namespace entity;
    return {{"Int8",   integer_impl_t::create(true,  integer_size_t::int_8)},
            {"UInt8",  integer_impl_t::create(false, integer_size_t::int_8)},
            {"Int16",  integer_impl_t::create(true,  integer_size_t::int_16)},
            {"UInt16", integer_impl_t::create(false, integer_size_t::int_16)},
            {"Int32",  integer_impl_t::create(true,  integer_size_t::int_32)},
            {"UInt32", integer_impl_t::create(false, integer_size_t::int_32)},
            {"Int64",  integer_impl_t::create(true,  integer_size_t::int_64)},
            {"UInt64", integer_impl_t::create(false, integer_size_t::int_64)}};
}

ast_t::ast_t( parser_impl_t &parser )
    : m_parser(parser)
    , m_root(ast_node_impl_t::create_root())
    , m_predefined_types(create_predefined_types())
{
    m_node_stack.push(m_root);
}

void ast_t::set_active_package( const std::string &fqn )
{
    assert(!m_active_package);
    m_parser.debug() << "Package:" << log_quote_t() << fqn;

    m_active_package = entity::package_impl_t::create();
    auto node = node_at(fqn, ast_flag_t::create_recursive |
                             ast_flag_t::free |
                             ast_flag_t::push);

    node->bind_entity(m_active_package);
}

void ast_t::start_type_collection( const std::string &fqn )
{
    m_parser.debug() << "TypeCollection:" << log_quote_t() << fqn;

    auto type_collection = entity::type_collection_impl_t::create();
    auto node = node_at(fqn, ast_flag_t::create_recursive |
                             ast_flag_t::relative |
                             ast_flag_t::free |
                             ast_flag_t::push);

    node->bind_entity(type_collection);
}

void ast_t::start_interface( const std::string &fqn )
{
    m_parser.debug() << "Interface:" << log_quote_t() << fqn;
    /* todo: create interface entity */
}

void ast_t::add_type( const std::string &fqn, const std::shared_ptr<entity::type_impl_t> &type )
{
    m_parser.debug() << "AddType:" << log_quote_t() << fqn;

    const auto flags = ast_flag_t::create | ast_flag_t::relative | ast_flag_t::free;
    auto node = node_at(fqn, flags);
    assert(node); /* node is created */

    node->bind_entity(type);
}

std::shared_ptr<entity::type_impl_t> ast_t::type( const std::string &fqn ) noexcept
{
    /* First, search starting from the current top node. If this node does not
     * contain it, then move to its parent node. And so on, until a root node is
     * reached. */
    auto base_node = m_node_stack.top();
    do {
        auto node = base_node->subnode_at(fqn);
        if ( node ) {
            m_parser.error() << "TODO: Implement getting the type entity";
            return nullptr;
        }
        base_node = base_node->parent();
    } while ( base_node /* == exists */ );

    /* If nothing is fined, then check if it is a predefined (a.k.a. standard)
     * type, like UInt32 or String. */
    auto it = m_predefined_types.find(fqn);
    if ( it != m_predefined_types.cend() ) {
        return it->second;
    }

    return nullptr;
}

std::shared_ptr<ast_node_impl_t>
        ast_t::node_at( const std::string &fqn, ast_flags_t flags ) noexcept
{
    auto &base_node =
            flags.is_set(ast_flag_t::relative) ? m_node_stack.top() : m_root;

    auto node = base_node->subnode_at(fqn, flags);
    if ( flags.is_set(ast_flag_t::push) ) {
        m_node_stack.push(node);
    }

    return node;
}

std::shared_ptr<ast_node_impl_t> ast_t::top_node() const
{
    return m_node_stack.top();
}

void ast_t::pop_node()
{
    m_node_stack.pop();
}

std::shared_ptr<ast_node_impl_t> ast_t::root_node() const
{
    return m_root;
}
