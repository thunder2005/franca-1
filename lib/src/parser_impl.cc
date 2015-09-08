/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "parser_impl.hh"

// local includes:
#include "log.hh"
#include "parse_error.hh"
#include "translation_unit.hh"
#include "input_context.hh"

// franca includes:
#include <franca/logger.hh>
#include <franca/input_factory.hh>
#include <franca/input_provider.hh>

// std includes:
#include <cassert>

using namespace franca;

parser_impl_t::parser_impl_t()
{
}

parser_impl_t::~parser_impl_t()
{
}

void parser_impl_t::set_logger( const std::shared_ptr<logger_t> &logger )
{
    assert(!m_logger);
    m_logger = logger;
}

void parser_impl_t::set_input_factory( const std::shared_ptr<input_factory_t> &factory )
{
    assert(!m_input_factory);
    m_input_factory = factory;
}

bool parser_impl_t::parse() noexcept
{
    debug() << "Executing parse()";

    auto input_names = m_input_factory->input_names();
    assert(!input_names.empty());

    try {
        for ( const auto &input_name : input_names ) {
            process_translation(input_name);
        }

    } catch ( parse_error_t &err ) {
        error() << err.what();
        return false;
    }

    return true;
}

void parser_impl_t::process_translation( const std::string &input_name )
{
    /* Create a translation unit for a given input name. */
    auto input_provider = m_input_factory->create_input(input_name);
    if ( !input_provider )
        throw parse_error_t("Internal error: input factory returned a nullptr.");

    m_translation_unit = std::make_shared<translation_unit_t>(
                *this, std::move(input_provider));
    m_translation_units.push(m_translation_unit);

    /* Process the input. */
    m_translation_unit->process_input();

    /* End a translation unit. */
    m_translation_units.pop();
}

#if 0
static void visit_all_dfs( const std::shared_ptr<ast_node_impl_t> &node, ast_visitor_t &visitor )
{
    node->accept_visitor(visitor);
    const auto &children = node->children();
    for ( const auto &child : children ) {
        visit_all_dfs(child.second, visitor);
    }
}

void parser_impl_t::visit_all_dfs( ast_visitor_t &visitor ) const
{
    ::visit_all_dfs(m_ast->root_node(), visitor);
}
#endif

input_context_t parser_impl_t::input_context() const noexcept
{
    if ( m_translation_unit ) {
        return m_translation_unit->input_context();
    } else {
        return {};
    }
}

log_t parser_impl_t::debug()
{
    return formated_log() << "Debug:";
}

log_t parser_impl_t::info()
{
    return formated_log() << "Info:";
}

log_t parser_impl_t::warn()
{
    return formated_log() << "Warning:";
}

log_t parser_impl_t::error()
{
    return formated_log() << "Error:";
}

log_t parser_impl_t::log()
{
    return log_t(m_logger.get());
}

log_t parser_impl_t::formated_log()
{
    if ( m_translation_unit ) {
        return m_translation_unit->formated_log();
    } else {
        return log();
    }
}
