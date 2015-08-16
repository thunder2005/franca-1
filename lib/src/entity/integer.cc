/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "franca/entity/integer.hh"

// local includes:
#include "entity/integer_impl.hh"

DEFINE_FRANCA_ENTITY(integer_t, integer_impl_t, type_t)

using namespace franca::entity;

bool integer_t::is_signed() const noexcept
{
    return impl()->is_signed();
}

attr::integer_size_t integer_t::size() const noexcept
{
    return impl()->size();
}
