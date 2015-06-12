/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// std includes:
#include <cstdint>

namespace franca {
namespace entity {

class version_t final
{
public:
    version_t() noexcept = default;
    version_t( std::uint32_t major, std::uint32_t minor )
        : m_major(major)
        , m_minor(minor)
    {
    }

public:
    bool is_valid() const noexcept { return (m_major > 0) && (m_minor > 0); }
    std::uint32_t major() const noexcept { return m_major; }
    std::uint32_t minor() const noexcept { return m_minor; }

private:
    std::uint32_t m_major = 0;
    std::uint32_t m_minor = 0;
};

} // namespace entity
} // namespace franca
