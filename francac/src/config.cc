/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "config.hh"

// std includes:
#include <iostream>

config_t::config_t()
    : m_dest("out")
{
}

bool config_t::process_args( int argc, char *argv[] ) noexcept
{
    /* save executable name */
    m_app_name = argv[0];

    /* for now, do not support options, treat all arguments as input */
    for ( int i = 1; i < argc; i++ ) {
        m_input_files.emplace_back(argv[i]);
    }

    return verify();
}

void config_t::print_usage() const noexcept
{
    std::cout << "Usage: " << m_app_name << " [<options>] <input files>" << std::endl;
    std::cout << "Options: "
                 "\n    -o <output dir>     set output directory [default: out]"
              << std::endl;
}

void config_t::dump() const noexcept
{
    std::cout << "Configuration dump:"
                 "\n    executable: " << m_app_name <<
                 "\n    dest: " << m_dest
              << std::endl;
    std::cout << "Input files:";
    for ( const auto &file : m_input_files ) {
        std::cout << "\n    " << file;
    }
    std::cout << std::endl;
}

bool config_t::verify() const noexcept
{
    if ( m_input_files.empty() ) {
        std::cout << "Error: No input files specified!" << std::endl;
        return false;
    }

    return true;
}
