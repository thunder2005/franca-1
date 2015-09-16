/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

namespace franca {

class log_t;
class loggable_impl_t;

class loggable_t
{
public:
    explicit loggable_t( const loggable_impl_t &impl ) noexcept;
    explicit loggable_t( const loggable_t &other ) noexcept;

public:
    log_t debug() const noexcept;
    log_t info() const noexcept;
    log_t warn() const noexcept;
    log_t error() const noexcept;

private:
    const loggable_impl_t &m_impl;
};

} // namespace franca
