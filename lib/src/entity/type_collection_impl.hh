/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// parent include:
#include "entity_impl.hh"

// franca includes:
#include "franca/entity/version.hh"

namespace franca {
namespace entity {

class type_collection_t;

class type_collection_impl_t final
        : public entity_impl_t
        , public std::enable_shared_from_this<type_collection_impl_t>
{
    DECL_FRANCA_ENTITY_IMPL(type_collection_t, type_collection_impl_t)

public:
    version_t version() const noexcept
    {
        return m_version;
    }

private:
    //! \reimp
    /* virtual */ void apply_version( std::uint32_t major, std::uint32_t minor ) override;

private:
    version_t m_version;
};

} // namespace entity
} // namespace franca
