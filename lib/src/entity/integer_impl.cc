/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "integer_impl.hh"

// franca includes:
#include "franca/entity/integer.hh"

using namespace franca;

std::shared_ptr<entity::integer_impl_t>
        entity::integer_impl_t::create( bool is_signed, entity::integer_size_t size )
{
    return std::make_shared<entity::integer_impl_t>(private_ctr(), is_signed, size);
}

entity::integer_impl_t::integer_impl_t( private_ctr, bool is_signed, integer_size_t size )
    : m_is_signed(is_signed)
    , m_size(size)
{
}

entity::integer_t entity::integer_impl_t::interface() noexcept
{
    return entity::integer_t(shared_from_this());
}

bool entity::integer_impl_t::is_signed() const noexcept
{
    return m_is_signed;
}

entity::integer_size_t entity::integer_impl_t::size() const noexcept
{
    return m_size;
}
