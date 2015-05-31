/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// std includes:
#include <memory>

namespace franca {
namespace entity {

class entity_impl_t
{
public:
    //! Virtual destructor.
    virtual ~entity_impl_t() = default;

public:
    entity_impl_t( const entity_impl_t & ) = delete;
    entity_impl_t &operator=( const entity_impl_t & ) = delete;

public:
    std::string fqn() const noexcept;
};

} // namespace entity
} // namespace franca
