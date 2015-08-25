/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "input_provider.hh"

// std includes:
#include <cassert>

input_provider_t::input_provider_t( const std::vector<std::string> &input_files )
{
    assert(!input_files.empty());

    m_filename = input_files.front();
    m_stream.open(m_filename);
}

std::string input_provider_t::name() const noexcept
{
    return m_filename;
}

std::istream &input_provider_t::stream() noexcept
{
    return m_stream;
}
