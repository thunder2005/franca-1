/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "franca/parser.hh"

// local includes:
#include "parser_impl.hh"
#include "entity/package_impl.hh"

// franca includes:
#include "franca/entity/package.hh"

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

void parser_t::set_input_factory( const std::shared_ptr<input_factory_t> &factory )
{
    m_impl->set_input_factory(factory);
}

bool parser_t::parse() noexcept
{
    return m_impl->parse();
}

#if 0
void parser_t::visit_all_dfs( ast_visitor_t &visitor ) const
{
    m_impl->visit_all_dfs(visitor);
}
#endif
