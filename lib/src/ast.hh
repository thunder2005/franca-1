/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// std includes:
#include <string>
#include <memory>
#include <stack>

namespace franca {

class parser_impl_t;
class ast_node_impl_t;

/*!
 * \brief Abstract syntax tree.
 */
class ast_t final
{
public:
    explicit ast_t( parser_impl_t &parser );
    ast_t( const ast_t & ) = delete;
    ast_t &operator=( const ast_t & ) = delete;

public:
    void set_active_package( const std::string &fqn );

public:
    /*!
     * \brief Get a node with a given FQN.
     * \param fqn Fully qualified name.
     * \param recursive Enable recursive node creation.
     * \return FQN node.
     *
     * This method returns a node with a given \e absolute FQN. If a node does
     * not exist, it and all missing parents are created. If a recursive mode is
     * disabled, \e fqn is allowed to be only one level deep.
     */
    std::shared_ptr<ast_node_impl_t>
            node_at( const std::string &fqn, bool recursive = true );

    /*!
     * \brief Get a node with a given relative FQN.
     * \param fqn Fully qualified name.
     * \param recursive Enable recursive node creation.
     * \return FQN node.
     *
     * This method returns a node with a given FQN, \e relative to the current
     * top node. If a node does not exist, it and all mising parents are created.
     * If a recursive mode is disabled, \e fqn is allowed to be only one level deep.
     *
     * \sa top_node()
     */
    std::shared_ptr<ast_node_impl_t>
            node_at_rel( const std::string &fqn, bool recursive = true );

    /*!
     * \brief Get a current top node.
     * \return Current FQN node.
     */
    std::shared_ptr<ast_node_impl_t> top_node() const;

    /*!
     * \brief Make a node with a given FQN a current top node.
     * \param fqn Fully qualified name.
     * \param recursive Enable recursive node creation.
     * \return FQN node.
     */
    std::shared_ptr<ast_node_impl_t>
            push_node( const std::string &fqn, bool recursive = true );

    /*!
     * \brief Make a node with a given relative FQN a current top node.
     * \param fqn Fully qualified name.
     * \param recursive Enable recursive node creation.
     * \return FQN node.
     */
    std::shared_ptr<ast_node_impl_t>
            push_node_rel( const std::string &fqn, bool recursive = true );

    /*!
     * \brief Restore a previous top node.
     */
    void pop_node();

private:
    parser_impl_t &m_parser;
    std::shared_ptr<ast_node_impl_t> m_root;
    std::stack<std::shared_ptr<ast_node_impl_t>> m_node_stack;
};

} // namespace franca
