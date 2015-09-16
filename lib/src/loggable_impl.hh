/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

namespace franca {

class log_t;

class loggable_impl_t
{
public:
    virtual log_t debug() const noexcept = 0;
    virtual log_t info() const noexcept = 0;
    virtual log_t warn() const noexcept = 0;
    virtual log_t error() const noexcept = 0;

protected:
    ~loggable_impl_t() = default;
};

} // namespace franca
