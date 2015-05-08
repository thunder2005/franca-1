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

class parser_impl_t final
{
public:
    parser_impl_t();
    ~parser_impl_t();

public:
    void set_logger( const std::shared_ptr<logger_t> &logger );
    log_t debug();

private:
    std::shared_ptr<logger_t> m_logger;
};

} // namespace franca
