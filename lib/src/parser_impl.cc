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
    m_line_nr = 0;
    m_input = input;
}

bool parser_impl_t::parse()
{
    assert(m_line_nr == 0);
    debug() << "parse()";

    auto &input = m_input->stream();

    bool ok = true;
    std::string line;

    try {
        do {
            m_line_nr++;
            std::getline(input, line);
            if ( input.fail() && !line.empty() )
                throw /* I/O error */ 0;
            debug() << "Line: \"" << line << "\"";
        } while ( !input.eof() );

        if ( !line.empty() )
            info() << "Input does not end with a newline";

    } catch ( ... ) {
        error() << "Error";
        ok = false;
    }

    return ok;
}

log_t parser_impl_t::debug()
{
    return log_t(m_logger.get()) << m_input->name() << ":" << m_line_nr << ": Debug:";
}

log_t parser_impl_t::info()
{
    return log_t(m_logger.get()) << m_input->name() << ":" << m_line_nr << ": Info:";
}

log_t parser_impl_t::warn()
{
    return log_t(m_logger.get()) << m_input->name() << ":" << m_line_nr << ": Warning:";
}

log_t parser_impl_t::error()
{
    return log_t(m_logger.get()) << m_input->name() << ":" << m_line_nr << ": Error:";
}
