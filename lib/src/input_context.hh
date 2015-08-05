/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// std includes:
#include <string>

namespace franca {

class input_context_t final
{
public:
    input_context_t() = default;
    input_context_t( const std::string &input_name,
                     std::size_t line_nr, std::size_t char_nr ) noexcept
        : m_input_name(input_name)
        , m_line_nr(line_nr)
        , m_char_nr(char_nr)
    {
    }

public:
    const std::string &input_name() const noexcept { return m_input_name; }
    std::size_t line_nr() const noexcept { return m_line_nr; }
    std::size_t char_nr() const noexcept { return m_char_nr; }

private:
    std::string m_input_name;  //!< Input (file) name.
    std::size_t m_line_nr = 0; //!< Line number.
    std::size_t m_char_nr = 0; //!< Character number.
};

} // namespace franca
