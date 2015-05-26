/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "stm.hh"

// local includes:
#include "state/package.hh"

using namespace franca;

stm_t::stm_t( parser_impl_t &parser )
    : m_parser(parser)
{
    m_ss.push(std::make_shared<state::package_t>(*this));
}

std::size_t stm_t::handle_input( const char *input )
{
    auto orig_input = input;
    auto &state = m_ss.top();
    state->set_input(input);

    input = state->goto_next_token();
    if ( input != orig_input )
        return input - orig_input;

    input = state->handle_token();
    return input - orig_input;
}

void stm_t::handle_eof()
{
}
