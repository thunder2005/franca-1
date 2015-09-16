/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// local includes:
#include "loggable.hh"

// std includes:
#include <stack>
#include <memory>

namespace franca {

class ast_t;
class input_cursor_t;
class state_t;
class translation_unit_t;

class stm_t final
        : public loggable_t
{
public:
    stm_t( translation_unit_t &tu, ast_t &ast );
    ~stm_t();

    stm_t( const stm_t & ) = delete;
    stm_t &operator=( const stm_t & ) = delete;

public:
    void handle_input( input_cursor_t &input_cursor );
    void handle_eof();

private:
    friend class state_t;
    translation_unit_t &tu() noexcept { return m_tu; }
    ast_t &ast() noexcept { return m_ast; }

    void simple_transit( const std::shared_ptr<state_t> &new_state ) noexcept;
    void push_transit( const std::shared_ptr<state_t> &new_state ) noexcept;
    void pop_transit() noexcept;

private:
    translation_unit_t &m_tu;
    ast_t &m_ast;
    std::stack<std::shared_ptr<state_t>> m_ss; // state stack
};

} // namespace franca
