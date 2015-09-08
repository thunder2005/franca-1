/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "input_factory.hh"

// local includes:
#include "input_provider.hh"

// std includes:
#include <cassert>

input_factory_t::input_factory_t( const std::vector<std::string> &input_files )
    : m_input_files(input_files)
{
    assert(!input_files.empty());
}

std::vector<std::string> input_factory_t::input_names() const noexcept
{
    return m_input_files;
}

std::unique_ptr<franca::input_provider_t> input_factory_t::create_input(
        const std::string &norm_name ) const noexcept
{
    return std::make_unique<input_provider_t>(norm_name);
}

std::string input_factory_t::normalise_name( const std::string &name ) const noexcept
{
    /* TODO: no normalisation for now... to implement a relative to absolute
     * filename conversion */
    return name;
}
