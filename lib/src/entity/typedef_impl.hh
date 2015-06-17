/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// parent include:
#include "entity/type_impl.hh"

namespace franca {
namespace entity {

class typedef_t;

class typedef_impl_t final: public type_impl_t
{
    DECL_FRANCA_ENTITY_IMPL_WARGS(typedef_t, typedef_impl_t,
                                  const std::shared_ptr<type_impl_t> &base_type)

public:
    const std::shared_ptr<type_impl_t> &base_type() const noexcept;

private:
    std::shared_ptr<type_impl_t> m_base_type;
};

} // namespace entity
} // namespace franca
