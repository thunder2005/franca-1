/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// testing:
#include <gtest/gtest.h>

// franca includes:
#include "parser_impl.hh"
#include "ast_node_impl.hh"
#include "ast.hh"

using namespace franca;

TEST(fqn, basic_node)
{
    auto node = ast_node_impl_t::create("node");
    ASSERT_STREQ("node", node->name().c_str());

    auto example_node = node->subnode_at("example", ast_flag_t::create_recursive);
    ASSERT_STREQ("example", example_node->name().c_str());

    auto new_node = example_node->subnode_at("new", ast_flag_t::create);
    ASSERT_STREQ("new", new_node->name().c_str());

    auto yet_new_node = node->subnode_at("example.new", ast_flag_t::create_recursive);
    ASSERT_EQ(new_node, yet_new_node);
    ASSERT_STREQ("node.example.new", new_node->fqn().c_str());
}

TEST(fqn, delete_node)
{
    auto root = ast_node_impl_t::create_root();
    auto node = root->subnode_at("this.is.an.example.node", ast_flag_t::create_recursive);

    ASSERT_STREQ("node", node->name().c_str());
    ASSERT_STREQ("this.is.an.example.node", node->fqn().c_str());

    auto new_base = node->parent()->parent();
    ASSERT_TRUE(new_base->has_parent());
    ASSERT_STREQ("an", new_base->name().c_str());

    /* delete root node, thus all nodes up to new_base should be deleted */
    root.reset();
    ASSERT_FALSE(new_base->has_parent());
    ASSERT_STREQ("an.example.node", node->fqn().c_str());
}

TEST(fqn, rebase_node)
{
    auto root = ast_node_impl_t::create_root();
    auto node_one = root->subnode_at("this.is.an.example.node", ast_flag_t::create_recursive);
    auto node_two = root->subnode_at("this.is.another.node", ast_flag_t::create_recursive);
    auto new_base = root->subnode_at("that", ast_flag_t::create);

    node_two->parent()->parent()->rebase(new_base);
    ASSERT_STREQ("that.is.an.example.node", node_one->fqn().c_str());
    ASSERT_STREQ("that.is.another.node", node_two->fqn().c_str());
}

#if 0
TEST(fqn, circular_rebase_node)
{
    auto root = ast_node_impl_t::create_root();
    auto node = root->subnode_at("this.is.an.example.node", ast_flag_t::create_recursive);

    root->subnode_at("this.is.an")->rebase(node);
    // todo: implement handling of circular rebase
    //ASSERT_STREQ("that.is.an.example.node", node->fqn().c_str());
}
#endif

TEST(fqn, basic_ast)
{
    parser_impl_t parser;
    loggable_t loggable(parser);
    ast_t ast(loggable);

    auto node = ast.node_at("this.is.node", ast_flag_t::create_recursive);
    ASSERT_EQ(ast.top_node(), node->parent()->parent()->parent());

    auto new_base = ast.node_at("this.is.base", ast_flag_t::create | ast_flag_t::push);
    ASSERT_EQ(ast.top_node(), new_base);

    node = ast.node_at("some", ast_flag_t::create | ast_flag_t::relative);
    ASSERT_STREQ("this.is.base.some", node->fqn().c_str());

    node = ast.node_at("some", ast_flag_t::create);
    ASSERT_STREQ("some", node->fqn().c_str());
    ASSERT_TRUE(node->parent()->is_root());
}
