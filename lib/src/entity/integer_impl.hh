/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// parent include:
#include "entity/type_impl.hh"

// franca includes:
#include "franca/entity/integer_size.hh"

namespace franca {
namespace entity {

class integer_t;

class integer_impl_t final: public type_impl_t
{
    DECL_FRANCA_ENTITY_IMPL_WARGS(integer_t, integer_impl_t,
                                  bool is_signed, integer_size_t size)

public:
    bool is_signed() const noexcept;
    integer_size_t size() const noexcept;

private:
    bool m_is_signed;
    integer_size_t m_size;
};

} // namespace entity
} // namespace franca
