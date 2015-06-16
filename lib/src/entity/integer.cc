/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "franca/entity/integer.hh"

// local includes:
#include "entity/integer_impl.hh"

DEFINE_ENTITY(integer_t, integer_impl_t)

using namespace franca;

bool entity::integer_t::is_signed() const noexcept
{
    return impl()->is_signed();
}

entity::integer_size_t entity::integer_t::size() const noexcept
{
    return impl()->size();
}
