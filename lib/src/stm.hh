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
class state_t;

class stm_t final
{
public:
    explicit stm_t( parser_impl_t &parser );

public:
    void handle_input( input_line_t &input );
    void handle_eof();

private:
    friend class state_t;
    parser_impl_t &parser() const noexcept { return m_parser; }

private:
    parser_impl_t &m_parser;
    std::stack<std::shared_ptr<state_t>> m_ss; // state stack
};

} // namespace franca
