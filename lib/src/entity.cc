/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "franca/entity.hh"

// local includes:
#include "entity_impl.hh"

using namespace franca;

namespace franca {

std::string entity_t::fqn() const noexcept
{
    return m_impl->fqn();
}

} // namespace franca
