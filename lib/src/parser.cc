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

void parser_t::set_input_provider( const std::shared_ptr<input_provider_t> &input )
{
    m_impl->set_input_provider(input);
}

bool parser_t::parse() noexcept
{
    return m_impl->parse();
}

std::vector<entity::package_t> parser_t::packages() const noexcept
{
    const auto package_impls = m_impl->packages();
    std::vector<entity::package_t> result;

    for ( const auto &package_impl : package_impls ) {
        result.push_back(package_impl->interface());
    }

    return result;
}

void parser_t::visit_all_dfs( ast_visitor_t &visitor ) const
{
    m_impl->visit_all_dfs(visitor);
}
