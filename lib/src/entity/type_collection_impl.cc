/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "type_collection_impl.hh"

// franca includes:
#include "franca/entity/type_collection.hh"

using namespace franca;

std::shared_ptr<entity::type_collection_impl_t> entity::type_collection_impl_t::create()
{
    return std::make_shared<entity::type_collection_impl_t>(private_ctr{});
}

entity::type_collection_impl_t::type_collection_impl_t( private_ctr )
{
}

entity::type_collection_t entity::type_collection_impl_t::interface() noexcept
{
    return entity::type_collection_t(shared_from_this());
}

void entity::type_collection_impl_t::apply_version( std::uint32_t major, std::uint32_t minor )
{
    m_version = { major, minor };
}
