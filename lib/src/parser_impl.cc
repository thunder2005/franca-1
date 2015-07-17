/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "parser_impl.hh"

// local includes:
#include "log.hh"
#include "stm.hh"
#include "parse_error.hh"
#include "ast.hh"
#include "ast_node_impl.hh"

// franca includes:
#include "franca/logger.hh"
#include "franca/input_provider.hh"

// std includes:
#include <cassert>

using namespace franca;

parser_impl_t::parser_impl_t()
    : m_ast(new ast_t(*this))
    , m_stm(new stm_t(*this, *m_ast))
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

void parser_impl_t::set_input_provider( const std::shared_ptr<input_provider_t> &input )
{
    assert(!m_input);
    m_input = input;
}

bool parser_impl_t::parse() noexcept
{
    assert(m_line.line_nr() == 0);
    debug() << "Executing parse()";

    try {
        auto &input = m_input->stream();
        std::string line;

        /* For each line in the input call a process_line() function. */
        do {
            std::getline(input, line);
            if ( input.fail() && !line.empty() )
                throw parse_error_t("I/O error.");
            process_line(line.c_str());
        } while ( !input.eof() );

        if ( !line.empty() )
            warn() << "Input does not end with a newline.";

        /* Check if STM is in a state, which allows EOF */
        m_stm->handle_eof();

    } catch ( parse_error_t &err ) {
        error() << err.what();
        return false;
    }

    return true;
}

void parser_impl_t::process_line( const char *line )
{
    assert(line != nullptr);

    m_line.reset(line);
    debug() << "Line:" << log_quote_t() << line;

    while ( !m_line.is_eol() ) {
        m_stm->handle_input(m_line);
    }
}

std::vector<std::shared_ptr<entity::package_impl_t> > parser_impl_t::packages() const noexcept
{
    const auto active_package = m_ast->active_package();
    if ( active_package ) {
        return { active_package };
    } else {
        return {};
    }
}

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

log_t parser_impl_t::debug()
{
    return log() << "Debug:";
}

log_t parser_impl_t::info()
{
    return log() << "Info:";
}

log_t parser_impl_t::warn()
{
    return log() << "Warning:";
}

log_t parser_impl_t::error()
{
    return log() << "Error:";
}

log_t parser_impl_t::log()
{
    m_line.update_baseline();
    return log_t(m_logger.get())
            << log_enable_nospace_t()
            << m_input->name() << ":" << m_line.line_nr() << ":" << m_line.char_nr() << ":"
            << log_disable_nospace_t();
}
