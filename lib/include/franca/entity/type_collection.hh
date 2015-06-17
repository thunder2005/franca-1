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
    DECL_FRANCA_ENTITY(type_collection_t, type_collection_impl_t)

public:
    version_t version() const noexcept;
};

} // namespace entity
} // namespace franca
