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
#include <franca/logger.hh>
#include <franca/input_provider.hh>

// std includes:
#include <sstream>

#define ASSERT_FQN(__exp_fqn, __entity)                                        \
    ASSERT_STREQ(__exp_fqn, (__entity).fqn().c_str())

namespace franca {

class test_logger_t final: public franca::logger_t
{
public:
    /* virtual */ void print( std::ostringstream &stream ) noexcept override;
};

class test_input_provider_t final: public franca::input_provider_t
{
public:
    test_input_provider_t( const char *fidl );
    /* virtual */ std::string name() const noexcept override;
    /* virtual */ std::istream &stream() noexcept override;

private:
    std::istringstream m_stream;
};

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

public:
    const parser_t &parser() const { return m_parser; }

private:
    parser_t m_parser;
    std::shared_ptr<test_logger_t> m_logger;
    std::shared_ptr<test_input_provider_t> m_input;
};

} // namespace franca
