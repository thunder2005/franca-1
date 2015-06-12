/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// parent include:
#include "franca/entity.hh"

namespace franca {
namespace entity {

class version_t;
class type_collection_impl_t;

class type_collection_t final: public entity_t
{
public:
    version_t version() const noexcept;

private:
    friend class type_collection_impl_t;
    explicit type_collection_t( const std::shared_ptr<type_collection_impl_t> &impl );
    const type_collection_impl_t *impl() const noexcept;
};

} // namespace entity
} // namespace franca
