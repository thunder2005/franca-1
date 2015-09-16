/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// parent include:
#include "franca/entity.hh"

// std includes:
#include <vector>

namespace franca {
namespace entity {

namespace attr {
class named_type_t;
}

class method_impl_t;

class method_t final: public entity_t
{
    DECL_FRANCA_ENTITY(method_t, method_impl_t)

public:
    std::vector<attr::named_type_t> in_args() const noexcept;
    std::vector<attr::named_type_t> out_args() const noexcept;
};

} // namespace entity
} // namespace franca
