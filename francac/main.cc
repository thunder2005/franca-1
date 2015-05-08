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

class stdout_logger_t final: public franca::logger_t
{
    void print( std::ostringstream &stream ) noexcept override
    {
        std::cout << stream.str() << std::endl;
    }
};

int main()
{
    franca::parser_t parser;
    parser.set_logger(std::make_shared<stdout_logger_t>());

    return 0;
}
