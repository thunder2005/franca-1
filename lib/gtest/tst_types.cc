/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// parent include:
#include "tst_common.hh"

using namespace franca;

class tst_type_collection: public test_t
{
};

TEST_F(tst_type_collection, empty_without_version)
{
    const char fidl[] =
            "package test.pkg\n"
            "\n\ntypeCollection testTypes\n"
            "{ \n   \t }\n";
    ASSERT_TRUE(parse(fidl));
}

TEST_F(tst_type_collection, empty_with_version)
{
    const char fidl[] =
            "package package\n"
            "typeCollection tc {\n"
            "    version { major 1 minor 0 }\n"
            "}\n";
    ASSERT_TRUE(parse(fidl));
}

TEST_F(tst_type_collection, empty_with_two_versions)
{
    const char fidl[] =
            "package package\n"
            "typeCollection tc {\n"
            "    version { major 1 minor 0 }\n"
            "    version { major 2 minor 0 }\n"
            "}\n";
    ASSERT_FALSE(parse(fidl));
}

TEST_F(tst_type_collection, typedef)
{
    const char fidl[] =
            "package tstTypeCollection.typedef\n"
            "typeCollection tc \n{\n"
            "    typedef myInt is UInt32\n"
            "}\n";
    ASSERT_TRUE(parse(fidl));
}

TEST_F(tst_type_collection, typedef_sanity_visitor)
{
    const char fidl[] =
            "package tstTypeCollection.typedef.visitor\n"
            "typeCollection tc \n{\n"
            "    typedef myLong  is UInt32\n"
            "    typedef myShort is UInt16\n"
            "}\n";
    ASSERT_TRUE(parse(fidl));

    test_printing_visitor_t visitor;
    parser().visit_all_dfs(visitor);
}
