/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// parent include:
#include "franca/entity.hh"

// franca includes:
#include "franca/entity/integer_size.hh"

namespace franca {
namespace entity {

class integer_impl_t;

class integer_t final: public entity_t
{
    DECL_ENTITY(integer_t, integer_impl_t)

public:
    integer_size_t size() const noexcept;
    bool is_signed() const noexcept;
};

} // namespace entity
} // namespace franca
