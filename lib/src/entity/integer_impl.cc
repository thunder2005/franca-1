/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "integer_impl.hh"

// franca includes:
#include "franca/entity/integer.hh"
#include "franca/ast_visitor.hh"

DEFINE_FRANCA_ENTITY_IMPL(integer_t, integer_impl_t)

using namespace franca::entity;

std::shared_ptr<integer_impl_t>
        integer_impl_t::create( bool is_signed, attr::integer_size_t size )
{
    return std::make_shared<integer_impl_t>(private_ctr(), is_signed, size);
}

integer_impl_t::integer_impl_t( private_ctr, bool is_signed, attr::integer_size_t size )
    : m_is_signed(is_signed)
    , m_size(size)
{
}

bool integer_impl_t::is_signed() const noexcept
{
    return m_is_signed;
}

attr::integer_size_t integer_impl_t::size() const noexcept
{
    return m_size;
}
