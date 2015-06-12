/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "franca/entity/type_collection.hh"

// local includes:
#include "entity/type_collection_impl.hh"

using namespace franca;

entity::type_collection_t::type_collection_t(
        const std::shared_ptr<type_collection_impl_t> &impl )
    : entity_t(impl)
{
}

const entity::type_collection_impl_t *entity::type_collection_t::impl() const noexcept
{
    return static_cast<type_collection_impl_t*>(m_impl.get());
}

entity::version_t entity::type_collection_t::version() const noexcept
{
    return impl()->version();
}
