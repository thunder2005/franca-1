/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "franca/entity/type_collection.hh"

// local includes:
#include "entity/type_collection_impl.hh"

DEFINE_FRANCA_ENTITY(type_collection_t, type_collection_impl_t, entity_t)

using namespace franca;

entity::version_t entity::type_collection_t::version() const noexcept
{
    return impl()->version();
}
