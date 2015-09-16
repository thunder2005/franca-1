/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "stm.hh"

// local includes:
#include "ast.hh"
#include "input_cursor.hh"
#include "log.hh"
#include "state/package.hh"
#include "translation_unit.hh"

using namespace franca;

stm_t::stm_t( translation_unit_t &tu , ast_t &ast )
    : loggable_t(tu)
    , m_tu(tu)
    , m_ast(ast)
{
    m_ss.push(std::make_shared<state::package_t>(*this));
}

stm_t::~stm_t()
{
}

void stm_t::handle_input( input_cursor_t &input_cursor )
{
    /* Make a copy of m_ss.top(). We need it because a token handler can perform
     * a state transit and the current state will be deleted, if not copied. */
    auto state = m_ss.top();
    debug() << "State:" << log_quote_t() << state->name() <<
               log_quote_t() << input_cursor.data();
    state->handle_token(input_cursor);
}

void stm_t::handle_eof()
{
    auto &state = m_ss.top();
    debug() << "EOF:" << log_quote_t() << state->name();
    state->handle_eof();
}

void stm_t::simple_transit( const std::shared_ptr<state_t> &new_state ) noexcept
{
    auto &cur_state = m_ss.top();
    debug() << "Transit:" << log_quote_t() << cur_state->name() << "->" <<
               log_quote_t() << new_state->name();
    cur_state = new_state;
}

void stm_t::push_transit( const std::shared_ptr<state_t> &new_state ) noexcept
{
    const auto &cur_state = m_ss.top();
    debug() << "Push:" << log_quote_t() << cur_state->name() << "->" <<
               log_quote_t() << new_state->name();
    m_ss.push(new_state);
}

void stm_t::pop_transit() noexcept
{
    const auto cur_state = m_ss.top();
    m_ss.pop();
    const auto &new_state = m_ss.top();
    debug() << "Pop:" << log_quote_t() << cur_state->name() << "->" <<
               log_quote_t() << new_state->name();
}
