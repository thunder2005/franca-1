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

class ast_object_t;

/*!
 * \brief AST node (implementation).
 *
 * This is a node in an abstract syntax tree (AST). This is an implementation
 * counterpart of \ref ast_node_t.
 */
class ast_node_impl_t final
        : public std::enable_shared_from_this<ast_node_impl_t>
{
    //! \internal
    class private_ctr {};

public:
    /*!
     * \brief Create a root node.
     * \return A shared pointer to a constructed root node.
     *
     * This function constructs a root node and returns a shared pointer to it.
     * A root node is a special node, which does not have a name, an FQN or a
     * parent. It cannot be rebased.
     */
    static std::shared_ptr<ast_node_impl_t> create_root();

    /*!
     * \brief Create a node.
     * \param name Name of the node.
     * \return A shared pointer to a constructed node.
     *
     * This function constructs an AST node with a given name. The name should
     * be a valid node name. The node will not have a parent.
     */
    static std::shared_ptr<ast_node_impl_t> create( const std::string &name );

    /*!
     * \brief Create a node.
     * \param name Name of the node.
     * \param parent Parent of the node.
     * \return A shared pointer to a constructed node.
     *
     * This function constructs an AST node with a given name and makes it a
     * child of a specified parent. The name should be a valid node name. The
     * parent should not have a child of the same name.
     */
    static std::shared_ptr<ast_node_impl_t>
            create( const std::string &name, const std::shared_ptr<ast_node_impl_t> &parent );

    //! \internal
    ast_node_impl_t( private_ctr );
    //! \internal
    explicit ast_node_impl_t( private_ctr, const std::string &name );
    //! \internal
    ast_node_impl_t( const ast_node_impl_t & ) = delete;
    //! \internal
    ast_node_impl_t &operator=( const ast_node_impl_t & ) = delete;

public:
    //! Get a name of the node.
    const std::string &name() const noexcept { return m_name; }

    //! Check if it is a root node.
    bool is_root() const noexcept { return m_name.empty(); }

    //! Get a fully qualified name of the node.
    std::string fqn() const;

    //! Get a parent node.
    std::shared_ptr<ast_node_impl_t> parent() const;

    //! Check if the node has a parent.
    bool has_parent() const;

    //! Get children nodes.
    const std::unordered_map<
        std::string, std::shared_ptr<ast_node_impl_t>> &children() const noexcept
    {
        return m_children;
    }

public:
    /*!
     * \brief Rebase this node to a new parent.
     * \param new_parent New parent.
     *
     * This function changes a parent of the node.
     */
    void rebase( const std::shared_ptr<ast_node_impl_t> &new_parent );

    /*!
     * \brief Get or construct a subnode.
     * \param name Name of a subnode.
     * \return A shared pointer to a subnode.
     *
     * This function returns a subnode with a given name. If such node does not
     * exist, it is constructed.
     */
    std::shared_ptr<ast_node_impl_t> subnode_at( const std::string &name );

    /*!
     * \brief Get or construct a subnode at a given path.
     * \param fqn Fully qualified name of a subnode.
     * \return A shared pointer to a subnode.
     *
     * This function returns a subnode at a given path, relative to this node.
     * Missing nodes of this path, if any, are constructed.
     */
    std::shared_ptr<ast_node_impl_t> subpath_at( const std::string &fqn );

private:
    const std::string m_name;
    std::weak_ptr<ast_node_impl_t> m_parent;
    std::unordered_map<std::string, std::shared_ptr<ast_node_impl_t>> m_children;
};

} // namespace franca
