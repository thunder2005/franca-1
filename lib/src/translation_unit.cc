/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "translation_unit.hh"

// local includes:
#include "log.hh"
#include "parser_impl.hh"
#include "parse_error.hh"
#include "ast.hh"
#include "stm.hh"
#include "input_cursor.hh"
#include "translation_unit.hh"
#include "input_context.hh"

// franca includes:
#include <franca/input_provider.hh>

// std includes:
#include <cassert>

using namespace franca;

translation_unit_t::translation_unit_t(
        parser_impl_t &parser,
        std::unique_ptr<input_provider_t> &&input_provider )
    : m_parser(parser)
    , m_input_provider(std::move(input_provider))
    , m_input_name(m_input_provider->name())
    , m_ast(std::make_unique<ast_t>(parser))
    , m_stm(std::make_unique<stm_t>(parser, *m_ast))
{
}

translation_unit_t::~translation_unit_t()
{
}

void translation_unit_t::process_input()
{
    /* For each line in the input call a process_line() function. */
    auto &input_stream = m_input_provider->stream();
    std::string line;

    do {
        std::getline(input_stream, line);
        if ( input_stream.fail() && !input_stream.eof() )
            throw parse_error_t("I/O error.");
        process_line(line.c_str());
    } while ( !input_stream.eof() );

    if ( !line.empty() )
        m_parser.warn() << "Input does not end with a newline.";

    /* Check if STM is in a state, which allows EOF */
    m_stm->handle_eof();
}

void translation_unit_t::process_line( const char *line )
{
    assert(line != nullptr);

    /* Gp to the next line. */
    m_line_nr++;
    input_cursor_t input_cursor(line, m_char_nr);

    m_parser.debug() << "Line:" << log_quote_t() << line;

    while ( !input_cursor.is_eol() ) {
        m_stm->handle_input(input_cursor);
    }
}

input_context_t translation_unit_t::input_context() const noexcept
{
    return { m_input_name, m_line_nr, m_char_nr };
}

log_t translation_unit_t::formated_log() const noexcept
{
    return m_parser.log()
            << log_enable_nospace_t()
            << m_input_name << ":" << m_line_nr << ":" << m_char_nr << ":"
            << log_disable_nospace_t();
}
