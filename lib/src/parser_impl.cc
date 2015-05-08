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

using namespace franca;

parser_impl_t::parser_impl_t()
{
}

parser_impl_t::~parser_impl_t()
{
}

void parser_impl_t::set_logger(const std::shared_ptr<logger_t> &logger )
{
    m_logger = logger;
    debug() << "Logger is set.";
}

log_t parser_impl_t::debug()
{
    return log_t(m_logger.get()) << "Debug:";
}
