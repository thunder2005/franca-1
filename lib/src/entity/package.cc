/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "franca/entity/package.hh"

// local includes:
#include "entity/package_impl.hh"

using namespace franca;

entity::package_t::package_t( const std::shared_ptr<package_impl_t> &impl )
    : entity_t(impl)
{
}
