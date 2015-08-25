/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// std includes:
#include <vector>
#include <string>

class config_t final
{
public:
    config_t();
    config_t( const config_t & ) = delete;
    config_t &operator=( const config_t & ) = delete;

public:
    bool process_args( int argc, char *argv[] ) noexcept;
    void print_usage() const noexcept;
    void dump() const noexcept;

public:
    const std::vector<std::string> &input_files() const noexcept
    {
        return m_input_files;
    }

private:
    bool verify() const noexcept;

private:
    std::string m_app_name;
    std::string m_dest;
    std::vector<std::string> m_input_files;
};
