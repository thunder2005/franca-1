/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "ast.hh"

// local includes:
#include "parser_impl.hh"
#include "log.hh"

using namespace franca;

ast_t::ast_t( parser_impl_t &parser )
    : m_parser(parser)
{
}

void ast_t::set_active_package( const std::string &fqn )
{
    m_parser.debug() << "Package:" << log_quote_t() << fqn;
}
