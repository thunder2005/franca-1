/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "franca/ast_node.hh"

// local includes:
#include "ast_node_impl.hh"

using namespace franca;

ast_node_t::ast_node_t( const std::shared_ptr<ast_node_impl_t> &impl )
    : m_impl(impl)
{
}

std::string ast_node_t::fqn() const
{
    return m_impl->fqn();
}

void ast_node_t::accept_visitor( ast_visitor_t &visitor )
{
    m_impl->accept_visitor(visitor);
}
