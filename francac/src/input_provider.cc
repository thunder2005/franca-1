/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "input_provider.hh"

// std includes:
#include <cassert>

input_provider_t::input_provider_t( const std::string &filename )
    : m_filename(filename)
    , m_stream(filename)
{
}

const std::string &input_provider_t::name() const noexcept
{
    return m_filename;
}

const std::string &input_provider_t::short_name() const noexcept
{
    return m_filename;
}

std::istream &input_provider_t::stream() noexcept
{
    return m_stream;
}
