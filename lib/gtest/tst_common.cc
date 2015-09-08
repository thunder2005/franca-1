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
#include <franca/ast_node.hh>
#include <franca/entity/package.hh>
#include <franca/entity/integer.hh>
#include <franca/entity/type_collection.hh>
#include <franca/entity/typedef.hh>

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

const std::string &test_input_provider_t::name() const noexcept
{
    static std::string s_name = "<test>";
    return s_name;
}

const std::string &test_input_provider_t::short_name() const noexcept
{
    return name();
}

test_input_factory_t::test_input_factory_t( const char *fidl )
    : m_fidl(fidl)
{
}

std::vector<std::string> test_input_factory_t::input_names() const noexcept
{
    return { "<test>" };
}

std::unique_ptr<franca::input_provider_t> test_input_factory_t::create_input(
        const std::string & /* norm_name */ ) const noexcept
{
    return std::make_unique<test_input_provider_t>(m_fidl);
}

std::string test_input_factory_t::normalise_name(
        const std::string &name ) const noexcept
{
    return name;
}

std::istream &test_input_provider_t::stream() noexcept
{
    return m_stream;
}

void test_printing_visitor_t::visit( const ast_node_t &node )
{
    std::cout << "AST: " << node.fqn() << " [node]" << std::endl;
}

void test_printing_visitor_t::visit( const entity::package_t &package )
{
    std::cout << "AST: " << package.fqn() << " [package]" << std::endl;
}

void test_printing_visitor_t::visit( const entity::type_collection_t &tc )
{
    std::cout << "AST: " << tc.fqn() << " [typeCollection]" << std::endl;
}

void test_printing_visitor_t::visit( const entity::typedef_t &type )
{
    std::cout << "AST: " << type.fqn() << " [type/typedef]" << std::endl;
}

void test_printing_visitor_t::visit(const entity::integer_t &type )
{
    std::cout << "AST: " << type.fqn() << " [type/int]" << std::endl;
}

void test_t::SetUp()
{
    m_logger = std::make_shared<test_logger_t>();
    m_parser.set_logger(m_logger);
}

void test_t::TearDown()
{
    m_input_factory.reset();
    m_logger.reset();
}

bool test_t::parse( const char *fidl )
{
    m_input_factory = std::make_shared<test_input_factory_t>(fidl);
    m_parser.set_input_factory(m_input_factory);
    return m_parser.parse();
}

class tst_common: public test_t
{
};

TEST_F(tst_common, empty_fidl)
{
    ASSERT_TRUE(parse(""));
    //ASSERT_EQ(0, parser().packages().size());
}

#if 0
TEST_F(tst_common, spaces_and_package_decl)
{
    ASSERT_TRUE(parse("    \t package test\n"));
    auto packages = parser().packages();
    ASSERT_EQ(1, packages.size());
    ASSERT_FQN("test", packages[0]);
}
#endif

TEST_F(tst_common, no_package_name)
{
    ASSERT_FALSE(parse("package"));
}

TEST_F(tst_common, newlines_and_invalid_keyword)
{
    ASSERT_FALSE(parse("\n   \ninterface"));
}

#if 0
TEST_F(tst_common, package_decl_no_newline)
{
    ASSERT_TRUE(parse("package test.franca.idl"));
    auto packages = parser().packages();
    ASSERT_EQ(1, packages.size());
    ASSERT_FQN("test.franca.idl", packages[0]);
}
#endif

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
