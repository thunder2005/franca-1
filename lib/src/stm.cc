/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "stm.hh"

// local includes:
#include "log.hh"
#include "parser_impl.hh"
#include "ast.hh"
#include "state/package.hh"

using namespace franca;

stm_t::stm_t( parser_impl_t &parser )
    : m_parser(parser)
    , m_ast(new ast_t(parser))
{
    m_ss.push(std::make_shared<state::package_t>(*this));
}

stm_t::~stm_t()
{
}

void stm_t::handle_input( input_line_t &input )
{
    /* Make a copy of m_ss.top(). We need it because a token handler can perform
     * a state transit and the current state will be deleted, if not copied. */
    auto state = m_ss.top();
    m_parser.debug() << "State:" << log_quote_t() << state->name() <<
                        log_quote_t() << input.mutable_data();
    state->handle_token(input);
}

void stm_t::handle_eof()
{
    auto &state = m_ss.top();
    m_parser.debug() << "EOF:" << log_quote_t() << state->name();
    state->handle_eof();
}

void stm_t::simple_transit( const std::shared_ptr<state_t> &new_state ) noexcept
{
    auto &cur_state = m_ss.top();
    m_parser.debug() << "Transit:" << log_quote_t() << cur_state->name() << "->" <<
                        log_quote_t() << new_state->name();
    cur_state = new_state;
}
