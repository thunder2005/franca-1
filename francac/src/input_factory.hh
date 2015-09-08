/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// parent include:
#include <franca/input_factory.hh>

// std includes:
#include <fstream>
#include <vector>

class input_factory_t final: public franca::input_factory_t
{
public:
    explicit input_factory_t( const std::vector<std::string> &input_files );

public:
    /* virtual */ std::vector<std::string> input_names() const noexcept override;
    /* virtual */ std::unique_ptr<franca::input_provider_t> create_input(
            const std::string &norm_name ) const noexcept override;
    /* virtual */ std::string normalise_name(
            const std::string &name ) const noexcept override;

private:
    std::vector<std::string> m_input_files;
};
