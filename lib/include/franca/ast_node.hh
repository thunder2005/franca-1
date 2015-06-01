/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// std includes:
#include <memory>
#include <string>
#include <unordered_map>

namespace franca {

class ast_node_impl_t;
class entity_t;

//! AST node.
class ast_node_t final
{
public:
    //! Get a name of the node.
    const std::string &name() const noexcept;

    //! Get a fully qualified name of the node.
    std::string fqn() const;

    //! Get a parent node.
    ast_node_t parent() const;

    //! Check if the node has a parent.
    bool has_parent() const;

    //! Get children nodes.
    std::unordered_map<std::string, ast_node_t> children() const;

    //! Get an associated entity.
    entity_t entity() const;

    //! Check if the node has an associated entity.
    bool has_entity() const;

private:
    friend class ast_node_impl_t;
    explicit ast_node_t( const std::shared_ptr<ast_node_impl_t> &impl );

private:
    std::shared_ptr<ast_node_impl_t> m_impl;
};

} // namespace franca
