/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// gtest include:
#include <gtest/gtest.h>

// franca includes:
#include <franca/parser.hh>

namespace franca {

class test_logger_t;
class test_input_provider_t;

/*!
 * \brief Base class for franca unit-tests.
 */
class test_t: public ::testing::Test
{
public:
    /* virtual */ void SetUp() override;
    /* virtual */ void TearDown() override;

public:
    bool parse( const char *fidl );

private:
    parser_t m_parser;
    std::shared_ptr<test_logger_t> m_logger;
    std::shared_ptr<test_input_provider_t> m_input;
};

} // namespace franca
