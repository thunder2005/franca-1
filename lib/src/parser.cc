/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "franca/parser.hh"

// franca includes:
#include "parser_impl.hh"

using namespace franca;

parser_t::parser_t()
    : m_impl(new parser_impl_t)
{
}

parser_t::~parser_t()
{
}

void parser_t::set_logger( std::unique_ptr<logger_t> &logger )
{
    m_impl->set_logger(logger);
}
