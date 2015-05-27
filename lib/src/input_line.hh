/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// std includes:
#include <cstddef>

namespace franca {

class input_line_t final
{
public:
    std::size_t line_nr() const noexcept { return m_line_nr; }
    std::size_t char_nr() const noexcept { return m_char_nr; }

public:
    void reset( const char *input ) noexcept
    {
        m_line_nr++;
        m_char_nr = 1;
        m_baseline = m_input = input;
    }

    bool is_eol() const noexcept { return *m_input == '\0'; }
    bool is_baseline() const noexcept { return m_input == m_baseline; }
    const char *&mutable_data() noexcept { return m_input; }

    void update_baseline() noexcept
    {
        m_char_nr += (m_input - m_baseline);
        m_baseline = m_input;
    }

private:
    std::size_t m_line_nr = 0; //!< Line number.
    std::size_t m_char_nr = 0; //!< Character number.
    const char *m_baseline = nullptr;
    const char *m_input = nullptr;
};

} // namespace franca
