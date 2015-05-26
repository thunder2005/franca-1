/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "package.hh"

// local includes:
#include "log.hh"

using namespace franca;

const char *state::package_t::handle_token()
{
    debug() << "Handling a token in state" << log_quote_t() << name();
    return m_input;
}

void state::package_t::handle_eof()
{
    debug() << "EOF in state" << name();
}
