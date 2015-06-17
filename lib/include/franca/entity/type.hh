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

class type_impl_t;

class type_t: public entity_t
{
    DECL_FRANCA_ENTITY(type_t, type_impl_t)
};

} // namespace entity
} // namespace franca
