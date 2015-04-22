/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// franca includes:
#include "franca/logger.hh"

// std includes:
#include <sstream>
#include <memory> // fixme (see below)

namespace franca {

class logger_t;
class logword_t;

class log_t final
{
public:
    inline explicit log_t( logger_t *logger ) noexcept;
    inline log_t ( log_t &&other ) noexcept;
    inline ~log_t() noexcept;
    inline std::ostringstream &stream() noexcept;

private:
    log_t( const log_t &other ) = delete;
    log_t &operator=( const log_t &other ) = delete;

private:
    friend class logword_t;
    inline void start_of_word() noexcept;
    inline void end_of_word() noexcept;

private:
    logger_t *m_logger;
    bool m_need_space;

    // fixme: remove unique_ptr as soon as ostringstream provides a
    //        move constructor (it should, according to C++11).
    std::unique_ptr<std::ostringstream> m_stream;
};

log_t::log_t( logger_t *logger ) noexcept
    : m_logger(logger)
    , m_need_space(false)
    , m_stream(new std::ostringstream) // fixme
{
}

log_t::log_t( log_t &&other ) noexcept
    : m_logger(std::move(other.m_logger))
    , m_need_space(std::move(other.m_need_space))
    , m_stream(std::move(other.m_stream))
{
    other.m_logger = nullptr;
}

log_t::~log_t() noexcept
{
    if ( m_logger ) {
        m_logger->print(stream());
    }
}

std::ostringstream &log_t::stream() noexcept
{
    return *m_stream.get();
}

void log_t::start_of_word() noexcept
{
    if ( m_need_space ) {
        stream() << ' ';
    }
}

void log_t::end_of_word() noexcept
{
    m_need_space = true;
}

/******************************************************************************
 * logword_t helper
 */

class logword_t final
{
public:
    inline logword_t( log_t &log ) noexcept;
    inline ~logword_t() noexcept;
    inline std::ostringstream &stream() const noexcept;

private:
    log_t &m_log;
};

logword_t::logword_t( log_t &log ) noexcept
    : m_log(log)
{
    m_log.start_of_word();
}

logword_t::~logword_t() noexcept
{
    m_log.end_of_word();
}

std::ostringstream &logword_t::stream() const noexcept
{
    return m_log.stream();
}

/******************************************************************************
 * loggig implementation for standard types
 */

template<typename T>
inline log_t &operator<<( log_t &log, const T &var )
{
    logword_t(log).stream() << var;
    return log;
}

template<typename T>
inline log_t &&operator<<( log_t &&log, const T &var )
{
    logword_t(log).stream() << var;
    return std::move(log);
}

} // namespace franca
