/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// parent include:
#include "tst_common.hh"

using namespace franca;

class tst_interface: public test_t
{
};

TEST_F(tst_interface, with_one_method)
{
    const char fidl[] =
            "package test.interfaces\n"
            "interface Summator  { \n"
            "    method Add { in{Int64 a\n"
            "                    Int64 b}out\n\t{Int64 c}}}\n";
    ASSERT_TRUE(parse(fidl));
}
