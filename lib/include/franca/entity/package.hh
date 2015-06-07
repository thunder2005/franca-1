/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// parent include:
#include "franca/entity.hh"

namespace franca {
namespace entity {

class package_impl_t;

class package_t final: public entity_t
{
private:
    friend class package_impl_t;
    explicit package_t( const std::shared_ptr<package_impl_t> &impl );
};

} // namespace entity
} // namespace franca
