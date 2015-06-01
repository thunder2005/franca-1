/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "franca/entity.hh"

// local includes:
#include "entity_impl.hh"
#include "ast_node_impl.hh"

// franca includes:
#include "franca/ast_node.hh"

// std includes:
#include <cassert>

using namespace franca;

std::string entity_t::fqn() const noexcept
{
    assert(m_impl->has_ast_node());
    return m_impl->ast_node()->fqn();
}

ast_node_t entity_t::ast_node() const noexcept
{
    assert(m_impl->has_ast_node());
    return m_impl->ast_node()->interface();
}
