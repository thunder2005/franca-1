/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "tst_common.hh"

using namespace franca;

void test_t::SetUp()
{
}

void test_t::TearDown()
{
}

bool test_t::parse( const char * /*fidl*/ )
{
    return true;
}

class tst_common: public test_t
{
};

TEST_F(tst_common, empty_fidl)
{
    ASSERT_TRUE(parse(""));
}
