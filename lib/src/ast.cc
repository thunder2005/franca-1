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

using namespace franca;

ast_t::ast_t( parser_impl_t &parser )
    : m_parser(parser)
    , m_root(ast_node_impl_t::create_root())
{
    m_node_stack.push(m_root);
}

void ast_t::set_active_package( const std::string &fqn )
{
    m_parser.debug() << "Package:" << log_quote_t() << fqn;
    auto node = node_at(fqn, ast_flag_t::create_recursive |
                             ast_flag_t::free |
                             ast_flag_t::push);
    node->has_entity(); // no-op
}

std::shared_ptr<ast_node_impl_t>
        ast_t::node_at( const std::string &fqn, ast_flags_t flags )
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
