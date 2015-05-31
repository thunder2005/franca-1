/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "franca/parser.hh"

// local includes:
#include "parser_impl.hh"

// franca includes:
#include "franca/package.hh"

using namespace franca;

parser_t::parser_t()
    : m_impl(new parser_impl_t)
{
}

parser_t::~parser_t()
{
}

void parser_t::set_logger(const std::shared_ptr<logger_t> &logger )
{
    m_impl->set_logger(logger);
}

void parser_t::set_input_provider( const std::shared_ptr<input_provider_t> &input )
{
    m_impl->set_input_provider(input);
}

bool parser_t::parse() noexcept
{
    return m_impl->parse();
}

std::vector<package_t> parser_t::packages() const noexcept
{
    return {};
}
