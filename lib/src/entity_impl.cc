/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "entity_impl.hh"

// std includes:
#include <cassert>

using namespace franca;

bool entity_impl_t::has_ast_node() const noexcept
{
    return !m_ast_node.expired();
}

std::shared_ptr<ast_node_impl_t> entity_impl_t::ast_node() const noexcept
{
    return m_ast_node.lock();
}

void entity_impl_t::apply_version( std::uint32_t /* major */, std::uint32_t /* minor */ )
{
    /* STM should not call this for entities which do not support version
     * specifications. */
    assert(false);
}
