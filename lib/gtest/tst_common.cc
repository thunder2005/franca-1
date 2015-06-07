/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "tst_common.hh"

// franca includes:
#include <franca/logger.hh>
#include <franca/input_provider.hh>
#include <franca/entity/package.hh>

using namespace franca;

void test_logger_t::print( std::ostringstream &stream ) noexcept
{
    /* print to console for now */
    std::cout << stream.str() << std::endl;
}

test_input_provider_t::test_input_provider_t( const char *fidl )
    : m_stream(fidl)
{
}

std::string test_input_provider_t::name() const noexcept
{
    return "<test>";
}

std::istream &test_input_provider_t::stream() noexcept
{
    return m_stream;
}

void test_t::SetUp()
{
    m_logger = std::make_shared<test_logger_t>();
    m_parser.set_logger(m_logger);
}

void test_t::TearDown()
{
    m_input.reset();
    m_logger.reset();
}

bool test_t::parse( const char *fidl )
{
    m_input = std::make_shared<test_input_provider_t>(fidl);
    m_parser.set_input_provider(m_input);
    return m_parser.parse();
}

class tst_common: public test_t
{
};

TEST_F(tst_common, empty_fidl)
{
    ASSERT_TRUE(parse(""));
    ASSERT_EQ(0, parser().packages().size());
}

TEST_F(tst_common, spaces_and_package_decl)
{
    ASSERT_TRUE(parse("    \t package test\n"));
    auto packages = parser().packages();
    ASSERT_EQ(1, packages.size());
    ASSERT_FQN("test", packages[0]);
}

TEST_F(tst_common, no_package_name)
{
    ASSERT_FALSE(parse("package"));
}

TEST_F(tst_common, newlines_and_invalid_keyword)
{
    ASSERT_FALSE(parse("\n   \ninterface"));
}

TEST_F(tst_common, package_decl_no_newline)
{
    ASSERT_TRUE(parse("package test.franca.idl"));
    auto packages = parser().packages();
    ASSERT_EQ(1, packages.size());
    ASSERT_FQN("test.franca.idl", packages[0]);
}

TEST_F(tst_common, package_name_contains_digits)
{
    ASSERT_TRUE(parse("package what.a.w0nderfull.n8"));
}

TEST_F(tst_common, invalid_package_name_two_dots)
{
    ASSERT_FALSE(parse("package two..dots"));
}

TEST_F(tst_common, invalid_package_name_first_dot)
{
    ASSERT_FALSE(parse("package .dot"));
}

TEST_F(tst_common, invalid_package_name_last_dot)
{
    ASSERT_FALSE(parse("package last."));
}

TEST_F(tst_common, invalid_package_name_digit)
{
    ASSERT_FALSE(parse("package 42name"));
}

TEST_F(tst_common, invalid_package_name_symbols)
{
    ASSERT_FALSE(parse("package h@llo"));
}
