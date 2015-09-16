/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "loggable.hh"

// local includes:
#include "loggable_impl.hh"
#include "log.hh"

using namespace franca;

loggable_t::loggable_t( const loggable_impl_t &impl ) noexcept
    : m_impl(impl)
{
}

loggable_t::loggable_t( const loggable_t &other ) noexcept
    : m_impl(other.m_impl)
{
}

log_t loggable_t::debug() const noexcept
{
    return m_impl.debug();
}

log_t loggable_t::info() const noexcept
{
    return m_impl.info();
}

log_t loggable_t::warn() const noexcept
{
    return m_impl.warn();
}

log_t loggable_t::error() const noexcept
{
    return m_impl.error();
}
