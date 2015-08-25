/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// parent include:
#include <franca/input_provider.hh>

// std includes:
#include <fstream>
#include <vector>

class input_provider_t final: public franca::input_provider_t
{
public:
    explicit input_provider_t( const std::vector<std::string> &input_files );
    /* virtual */ std::string name() const noexcept;
    /* virtual */ std::istream &stream() noexcept;

private:
    std::string m_filename;
    std::ifstream m_stream;
};
