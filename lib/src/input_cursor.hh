/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// std includes:
#include <cstddef>
#include <cassert>

namespace franca {

class input_cursor_t final
{
public:
    input_cursor_t( const char *&input_line, std::size_t &char_nr )
        : m_data(input_line)
        , m_char_nr(char_nr)
    {
        m_char_nr = 1;
    }

public:
    const char *data() const noexcept { return m_data; }
    bool is_eol() const noexcept { return *m_data == '\0'; }

    void update( const char *new_data )
    {
        assert(new_data >= m_data && "Cannot move the cursor to the past");
        m_char_nr += (new_data - m_data);
        m_data = new_data;
    }

private:
    const char *&m_data;
    std::size_t &m_char_nr;
};

class input_cursor_updater_t final
{
public:
    input_cursor_updater_t( input_cursor_t &input_cursor, const char *&local_copy )
        : m_input_cursor(input_cursor)
        , m_local_copy(local_copy)
    {
        m_local_copy = m_input_cursor.data();
    }

    ~input_cursor_updater_t()
    {
        m_input_cursor.update(m_local_copy);
    }

private:
    input_cursor_t &m_input_cursor;
    const char *&m_local_copy;
};

} // namespace franca
