/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// parent include:
#include "entity_impl.hh"

namespace franca {
namespace entity {

class package_t;

class package_impl_t final
        : public entity_impl_t
        , public std::enable_shared_from_this<package_impl_t>
{
    DECL_FRANCA_ENTITY_IMPL(package_t, package_impl_t)
};

} // namespace entity
} // namespace franca
