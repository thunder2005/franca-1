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
#include "input_factory.hh"

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

    s_parser.set_logger(std::make_shared<stdout_logger_t>());
    s_parser.set_input_factory(
                std::make_shared<input_factory_t>(s_config.input_files()));

    if ( !s_parser.parse() ) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
