/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "package_impl.hh"

// franca includes:
#include "franca/entity/package.hh"

using namespace franca;

std::shared_ptr<entity::package_impl_t> entity::package_impl_t::create()
{
    return std::make_shared<entity::package_impl_t>(private_ctr{});
}

entity::package_impl_t::package_impl_t( private_ctr )
{
}

entity::package_t entity::package_impl_t::interface() noexcept
{
    return entity::package_t(shared_from_this());
}
