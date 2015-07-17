/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "type_collection_impl.hh"

// franca includes:
#include "franca/entity/type_collection.hh"
#include "franca/ast_visitor.hh"

DEFINE_FRANCA_ENTITY_IMPL(type_collection_t, type_collection_impl_t)

using namespace franca::entity;

std::shared_ptr<type_collection_impl_t> type_collection_impl_t::create()
{
    return std::make_shared<type_collection_impl_t>(private_ctr{});
}

type_collection_impl_t::type_collection_impl_t( private_ctr )
{
}

void type_collection_impl_t::apply_version( std::uint32_t major, std::uint32_t minor )
{
    m_version = { major, minor };
}
