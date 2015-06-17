/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// parent include:
#include "franca/entity/type.hh"

namespace franca {
namespace entity {

class typedef_impl_t;

class typedef_t final: public type_t
{
    DECL_FRANCA_ENTITY(typedef_t, typedef_impl_t)

public:
    type_t base_type() const noexcept;
};

} // namespace entity
} // namespace franca
