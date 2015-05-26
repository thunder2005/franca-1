/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "state.hh"

// local includes:
#include "log.hh"
#include "stm.hh"
#include "parser_impl.hh"

using namespace franca;

state_t::state_t( const char *name, stm_t &stm )
    : m_input(nullptr)
    , m_name(name)
    , m_stm(stm)
{
}

const char *state_t::goto_next_token()
{
    return m_input;
}

void state_t::handle_eof()
{
    /* default implementation does nothing */
}

log_t state_t::debug()
{
    return m_stm.parser().debug();
}

log_t state_t::info()
{
    return m_stm.parser().info();
}

log_t state_t::warn()
{
    return m_stm.parser().warn();
}

log_t state_t::error()
{
    return m_stm.parser().error();
}
