/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// testing:
#include <gtest/gtest.h>

// franca includes:
#include "ast_node_impl.hh"

using namespace franca;

TEST(fqn, basic_node)
{
    auto node = ast_node_impl_t::create("node");
    ASSERT_STREQ("node", node->name().c_str());

    auto example_node = node->subpath_at("example");
    ASSERT_STREQ("example", example_node->name().c_str());

    auto new_node = example_node->subnode_at("new");
    ASSERT_STREQ("new", new_node->name().c_str());

    auto yet_new_node = node->subpath_at("example.new");
    ASSERT_EQ(new_node, yet_new_node);
    ASSERT_STREQ("node.example.new", new_node->fqn().c_str());
}

TEST(fqn, delete_node)
{
    auto root = ast_node_impl_t::create_root();
    auto node = root->subpath_at("this.is.an.example.node");

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
    auto node_one = root->subpath_at("this.is.an.example.node");
    auto node_two = root->subpath_at("this.is.another.node");
    auto new_base = root->subnode_at("that");

    node_two->parent()->parent()->rebase(new_base);
    ASSERT_STREQ("that.is.an.example.node", node_one->fqn().c_str());
    ASSERT_STREQ("that.is.another.node", node_two->fqn().c_str());
}

TEST(fqn, circular_rebase_node)
{
    auto root = ast_node_impl_t::create_root();
    auto node = root->subpath_at("this.is.an.example.node");

    root->subpath_at("this.is.an")->rebase(node);
    // todo: implement handling of circular rebase
    //ASSERT_STREQ("that.is.an.example.node", node->fqn().c_str());
}
