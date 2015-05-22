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
class log_word_t;
class log_enable_nospace_t;
class log_disable_nospace_t;
class log_quote_t;

class log_t final
{
public:
    inline explicit log_t( logger_t *logger ) noexcept;
    inline log_t ( log_t &&other ) noexcept;
    inline ~log_t() noexcept;
    inline std::ostringstream &stream() noexcept;

public:
    inline log_t &&operator<<( const log_enable_nospace_t & ) && noexcept;
    inline log_t &&operator<<( const log_disable_nospace_t & ) && noexcept;
    inline log_t &&operator<<( const log_quote_t & ) && noexcept;

private:
    log_t( const log_t &other ) = delete;
    log_t &operator=( const log_t &other ) = delete;

private:
    friend class log_word_t;
    inline void start_of_word() noexcept;
    inline void end_of_word() noexcept;

private:
    logger_t *m_logger;
    bool m_need_space;
    bool m_enable_nospace;
    bool m_need_quote;

    // fixme: remove unique_ptr as soon as ostringstream provides a
    //        move constructor (it should, according to C++11).
    std::unique_ptr<std::ostringstream> m_stream;
};

log_t::log_t( logger_t *logger ) noexcept
    : m_logger(logger)
    , m_need_space(false)
    , m_enable_nospace(false)
    , m_need_quote(false)
    , m_stream(new std::ostringstream) // fixme
{
}

log_t::log_t( log_t &&other ) noexcept
    : m_logger(std::move(other.m_logger))
    , m_need_space(std::move(other.m_need_space))
    , m_enable_nospace(std::move(other.m_enable_nospace))
    , m_need_quote(std::move(other.m_need_quote))
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

log_t &&log_t::operator<<( const log_enable_nospace_t & ) && noexcept
{
    m_enable_nospace = true;
    return std::move(*this);
}

log_t &&log_t::operator<<( const log_disable_nospace_t & ) && noexcept
{
    m_enable_nospace = false;
    return std::move(*this);
}

log_t &&log_t::operator<<( const log_quote_t & ) && noexcept
{
    m_need_quote = true;
    return std::move(*this);
}

void log_t::start_of_word() noexcept
{
    if ( m_need_space && !m_enable_nospace ) {
        stream() << ' ';
    }
    if ( m_need_quote ) {
        stream() << '"';
    }
}

void log_t::end_of_word() noexcept
{
    m_need_space = true;
    if ( m_need_quote ) {
        stream() << '"';
        m_need_quote = false;
    }
}

/******************************************************************************
 * log_word_t helper
 */

class log_word_t final
{
public:
    inline log_word_t( log_t &log ) noexcept;
    inline ~log_word_t() noexcept;
    inline std::ostringstream &stream() const noexcept;

private:
    log_t &m_log;
};

log_word_t::log_word_t( log_t &log ) noexcept
    : m_log(log)
{
    m_log.start_of_word();
}

log_word_t::~log_word_t() noexcept
{
    m_log.end_of_word();
}

std::ostringstream &log_word_t::stream() const noexcept
{
    return m_log.stream();
}

/******************************************************************************
 * log_nospace_t and log_quote_t helpers
 */

class log_enable_nospace_t {};
class log_disable_nospace_t {};
class log_quote_t {};

/******************************************************************************
 * loggig implementation for standard types
 */

template<typename T>
inline log_t &operator<<( log_t &log, const T &var )
{
    log_word_t(log).stream() << var;
    return log;
}

template<typename T>
inline log_t &&operator<<( log_t &&log, const T &var )
{
    log_word_t(log).stream() << var;
    return std::move(log);
}

} // namespace franca
