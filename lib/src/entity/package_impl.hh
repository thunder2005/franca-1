/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// parent include:
#include "entity_impl.hh"

namespace franca {
namespace entity {

class package_t;

class package_impl_t final
        : public entity_impl_t
        , public std::enable_shared_from_this<package_impl_t>
{
public:
    /*!
     * \brief Create a package entity.
     * \return A shared pointer to a constructed entity.
     *
     * This function constructs a package entity.
     */
    static std::shared_ptr<package_impl_t> create();

    //! \internal
    explicit package_impl_t( private_ctr );

public:
    //! Create a public interface object.
    package_t interface() noexcept;
};

} // namespace entity
} // namespace franca
