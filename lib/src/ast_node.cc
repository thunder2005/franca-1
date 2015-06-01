/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "franca/ast_node.hh"

using namespace franca;

ast_node_t::ast_node_t( const std::shared_ptr<ast_node_impl_t> &impl )
    : m_impl(impl)
{
}
