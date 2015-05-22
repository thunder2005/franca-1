/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "stm.hh"

using namespace franca;

std::size_t stm_t::handle_token( const char *token )
{
    return *token;
}

void stm_t::handle_eof()
{
}
