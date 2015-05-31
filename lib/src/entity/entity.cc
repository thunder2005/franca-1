/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "franca/entity/entity.hh"

// local includes:
#include "entity_impl.hh"

using namespace franca;

std::string entity::entity_t::fqn() const noexcept
{
    return m_impl->fqn();
}
