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
#include "state/package.hh"

using namespace franca;

stm_t::stm_t( parser_impl_t &parser )
    : m_parser(parser)
{
    m_ss.push(std::make_shared<state::package_t>(*this));
}

void stm_t::handle_input( input_line_t &input )
{
    auto &state = m_ss.top();
    m_parser.debug() << "State" << log_quote_t() << state->name();
    state->handle_token(input);
}

void stm_t::handle_eof()
{
    auto &state = m_ss.top();
    m_parser.debug() << "EOF in state" << log_quote_t() << state->name();
    state->handle_eof();
}
