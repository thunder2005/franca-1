/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// std includes:
#include <type_traits>

namespace franca {

enum class ast_flag_t
{
    create           = (1 << 0),
    create_recursive = (1 << 1) | create,
    create_exclusive = (1 << 2) | create,
    free             = (1 << 3),
    relative         = (1 << 4),
    push             = (1 << 5)
};

class ast_flags_t final
{
public:
    using type = std::underlying_type<ast_flag_t>::type;

public:
    ast_flags_t()
        : m_flags(0)
    {
    }

    ast_flags_t( ast_flag_t flag )
        : ast_flags_t(static_cast<type>(flag))
    {
    }

    ast_flags_t operator|( ast_flag_t r_flag )
    {
        return m_flags | static_cast<type>(r_flag);
    }

    bool is_set( ast_flags_t flags )
    {
        return (m_flags & flags.m_flags) == flags.m_flags;
    }

private:
    ast_flags_t( type flags )
        : m_flags(flags)
    {
    }

private:
    type m_flags;
};

inline ast_flags_t operator|( ast_flag_t l_flag, ast_flag_t r_flag )
{
    return ast_flags_t(l_flag) | r_flag;
}

} // namespace franca
