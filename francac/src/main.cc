/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// franca includes:
#include <franca/parser.hh>
#include <franca/logger.hh>

// std includes:
#include <iostream>
#include <sstream>

// local includes:
#include "config.hh"

namespace {

class stdout_logger_t final: public franca::logger_t
{
    void print( std::ostringstream &stream ) noexcept override
    {
        std::cout << stream.str() << std::endl;
    }
};

config_t s_config;
franca::parser_t s_parser;

} // anonymous namespace

int main( int argc, char *argv[] )
{
    if ( !s_config.process_args(argc, argv) ) {
        s_config.print_usage();
        return EXIT_FAILURE;
    }
    s_config.dump();

    return EXIT_SUCCESS;
}
