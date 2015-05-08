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
}
