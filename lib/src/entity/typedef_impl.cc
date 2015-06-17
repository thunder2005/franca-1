/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "typedef_impl.hh"

// franca includes:
#include "franca/entity/typedef.hh"

using namespace franca;
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

typedef_t typedef_impl_t::interface() noexcept
{
    return typedef_t(std::static_pointer_cast<typedef_impl_t>(shared_from_this()));
}

const std::shared_ptr<type_impl_t> &typedef_impl_t::base_type() const noexcept
{
    return m_base_type;
}
