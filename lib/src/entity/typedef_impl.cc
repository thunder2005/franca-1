/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "typedef_impl.hh"

// franca includes:
#include "franca/entity/typedef.hh"
#include "franca/ast_visitor.hh"

DEFINE_FRANCA_ENTITY_IMPL(typedef_t, typedef_impl_t)

using namespace franca::entity;

std::shared_ptr<typedef_impl_t> typedef_impl_t::create(
        const std::shared_ptr<type_impl_t> &base_type )
{
    return std::make_shared<typedef_impl_t>(private_ctr(), base_type);
}


typedef_impl_t::typedef_impl_t( private_ctr, const std::shared_ptr<type_impl_t> &base_type )
    : m_base_type(base_type)
{
}

const std::shared_ptr<type_impl_t> &typedef_impl_t::base_type() const noexcept
{
    return m_base_type;
}
