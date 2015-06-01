/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "entity_impl.hh"

using namespace franca;

bool entity_impl_t::has_ast_node() const noexcept
{
    return !m_ast_node.expired();
}

std::shared_ptr<ast_node_impl_t> entity_impl_t::ast_node() const noexcept
{
    return m_ast_node.lock();
}
