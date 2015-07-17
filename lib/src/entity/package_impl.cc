/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "package_impl.hh"

// franca includes:
#include "franca/entity/package.hh"
#include "franca/ast_visitor.hh"

DEFINE_FRANCA_ENTITY_IMPL(package_t, package_impl_t)

using namespace franca::entity;

std::shared_ptr<package_impl_t> package_impl_t::create()
{
    return std::make_shared<package_impl_t>(private_ctr{});
}

package_impl_t::package_impl_t( private_ctr )
{
}
