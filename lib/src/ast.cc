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
{
}

void ast_t::set_active_package( const std::string &fqn )
{
    m_parser.debug() << "Package:" << log_quote_t() << fqn;
}

std::shared_ptr<ast_node_impl_t>
        ast_t::node_at(const std::string &fqn, bool recursive )
{
    if ( recursive ) {
        return m_root->subpath_at(fqn);
    } else {
        return m_root->subnode_at(fqn);
    }
}

std::shared_ptr<ast_node_impl_t>
        ast_t::node_at_rel( const std::string &fqn, bool recursive )
{
    if ( recursive ) {
        return top_node()->subpath_at(fqn);
    } else {
        return top_node()->subnode_at(fqn);
    }
}

std::shared_ptr<ast_node_impl_t> ast_t::top_node() const
{
    return m_node_stack.top();
}

std::shared_ptr<ast_node_impl_t>
        ast_t::push_node( const std::string &fqn, bool recursive )
{
    auto node = node_at(fqn, recursive);
    m_node_stack.push(node);
    return node;
}

std::shared_ptr<ast_node_impl_t>
        ast_t::push_node_rel( const std::string &fqn, bool recursive )
{
    auto node = node_at_rel(fqn, recursive);
    m_node_stack.push(node);
    return node;
}

void ast_t::pop_node()
{
    m_node_stack.pop();
}
