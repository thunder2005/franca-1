/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "parser_impl.hh"

// local includes:
#include "log.hh"

// franca includes:
#include "franca/logger.hh"
#include "franca/input_provider.hh"

// std includes:
#include <cassert>

using namespace franca;

parser_impl_t::parser_impl_t()
    : m_line_nr(0)
    , m_char_nr(0)
{
}

parser_impl_t::~parser_impl_t()
{
}

void parser_impl_t::set_logger(const std::shared_ptr<logger_t> &logger )
{
    assert(!m_logger);
    m_logger = logger;
}

void parser_impl_t::set_input_provider( const std::shared_ptr<input_provider_t> &input )
{
    assert(!m_input);
    m_input = input;
}

bool parser_impl_t::parse()
{
    assert(m_line_nr == 0);
    debug() << "Executing parse()";

    auto &input = m_input->stream();

    std::string line;

    try {
        do {
            m_line_nr++;
            std::getline(input, line);
            if ( input.fail() && !line.empty() )
                throw /* I/O error */ 0;
            debug() << "Line:" << log_quote_t() << line;
        } while ( !input.eof() );

        if ( !line.empty() )
            warn() << "Input does not end with a newline";

    } catch ( ... ) {
        error() << "Error";
        return false;
    }

    return true;
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
