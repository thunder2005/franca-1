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

class type_t;

class type_impl_t
        : public entity_impl_t
        , public std::enable_shared_from_this<type_impl_t>
{
    using entity_impl_t::entity_impl_t;

public:
    type_t interface() noexcept;
};

} // namespace entity
} // namespace franca
