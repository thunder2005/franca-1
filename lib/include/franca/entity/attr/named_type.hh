/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// franca includes:
#include "franca/entity/type.hh"

// std includes:
#include <cassert>

namespace franca {
namespace entity {
namespace attr {

class named_type_t final
{
public:
    named_type_t() = default;
    named_type_t( const std::string &name, const type_t &type )
        : m_name(name)
        , m_type(type)
    {
        assert(!name.empty());
        assert(!type.fqn().empty());
    }

public:
    const std::string &name() const noexcept { return m_name; }
    const type_t &type() const noexcept { return m_type; }

private:
    std::string m_name;
    type_t m_type;
};

} // namespace attr
} // namespace entity
} // namespace franca
