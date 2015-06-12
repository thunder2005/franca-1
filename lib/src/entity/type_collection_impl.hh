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
public:
    /*!
     * \brief Create a type collection entity.
     * \return A shared pointer to a constructed entity.
     *
     * This function constructs a type collection entity.
     */
    static std::shared_ptr<type_collection_impl_t> create();

    //! \internal
    explicit type_collection_impl_t( private_ctr );

public:
    //! Create a public interface object.
    type_collection_t interface() noexcept;

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
