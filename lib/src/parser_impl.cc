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

// franca includes:
#include "franca/logger.hh"
#include "franca/input_provider.hh"

// std includes:
#include <cassert>

using namespace franca;

parser_impl_t::parser_impl_t()
    : m_stm(new stm_t)
    , m_line_nr(0)
    , m_char_nr(0)
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
    assert(m_line_nr == 0);
    debug() << "Executing parse()";

    try {
        auto &input = m_input->stream();
        std::string line;

        /* For each line in the input call a process_line() function. */
        do {
            m_line_nr++;
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
    m_char_nr = 1;

    debug() << "Line:" << log_quote_t() << line;

    while ( *line != '\0' ) {
        auto handled_chars = m_stm->handle_token(line);

        /* If we did not advance at least one character, then we have an issue
         * in STM, which leads to an infinite loop. This check prevents looping
         * forever. */
        if ( handled_chars == 0 ) {
            throw parse_error_t("Internal infinite loop detected.");
        }

        m_char_nr += handled_chars;
        line += handled_chars;
    }
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
    return log_t(m_logger.get())
            << log_enable_nospace_t()
            << m_input->name() << ":" << m_line_nr << ":" << m_char_nr << ":"
            << log_disable_nospace_t();
}
