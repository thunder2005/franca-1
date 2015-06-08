/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// std includes:
#include <stack>
#include <memory>

namespace franca {

class parser_impl_t;
class input_line_t;
class ast_t;
class state_t;

class stm_t final
{
public:
    stm_t( parser_impl_t &parser, ast_t &ast );
    ~stm_t();

    stm_t( const stm_t & ) = delete;
    stm_t &operator=( const stm_t & ) = delete;

public:
    void handle_input( input_line_t &input );
    void handle_eof();

private:
    friend class state_t;
    parser_impl_t &parser() const noexcept { return m_parser; }
    ast_t &ast() const noexcept { return m_ast; }

    void simple_transit( const std::shared_ptr<state_t> &new_state ) noexcept;

private:
    parser_impl_t &m_parser;
    ast_t &m_ast;
    std::stack<std::shared_ptr<state_t>> m_ss; // state stack
};

} // namespace franca
