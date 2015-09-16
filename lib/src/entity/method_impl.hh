/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// parent include:
#include "entity_impl.hh"

// local includes:
#include "named_entity.hh"
#include "inout.hh"

// std includes:
#include <vector>

namespace franca {
namespace entity {

class method_t;

class method_impl_t final
        : public entity_impl_t
        , public std::enable_shared_from_this<method_impl_t>
{
    DECL_FRANCA_ENTITY_IMPL(method_t, method_impl_t)

public:
    void set_direction( inout_t direction ) noexcept
    {
        m_direction = direction;
    }

private:
    //! \reimp
    /* virtual */ void apply_argument( const named_entity_t &arg ) override;

private:
    inout_t m_direction = inout_t::undefined;
    std::vector<named_entity_t> m_in_args;
    std::vector<named_entity_t> m_out_args;
};

} // namespace entity
} // namespace franca
