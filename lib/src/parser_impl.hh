/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// std includes:
#include <memory>

namespace franca {

class logger_t;
class log_t;
class input_provider_t;

class parser_impl_t final
{
public:
    parser_impl_t();
    ~parser_impl_t();

public:
    parser_impl_t( const parser_impl_t & ) = delete;
    parser_impl_t &operator=( const parser_impl_t & ) = delete;

public:
    void set_logger( const std::shared_ptr<logger_t> &logger );
    void set_input_provider( const std::shared_ptr<input_provider_t> &input );
    bool parse();

public:
    log_t debug();
    log_t info();
    log_t warn();
    log_t error();

private:
    log_t log();

private:
    std::shared_ptr<logger_t> m_logger;
    std::shared_ptr<input_provider_t> m_input;
    std::size_t m_line_nr; //!< Line number.
    std::size_t m_char_nr; //!< Character number.
};

} // namespace franca
