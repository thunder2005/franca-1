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

// local includes:
#include "ast_flags.hh"

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
     * \param flags AST flags.
     * \return AST node.
     *
     * This method returns an AST node with a given \e absolute FQN.
     *
     * The exact behaviour depends on set \e flags. Please see \ref ast_flag_t
     * for a detailed description.
     */
    std::shared_ptr<ast_node_impl_t>
            node_at( const std::string &fqn, ast_flags_t flags );

    /*!
     * \brief Get a current top node.
     * \return Current FQN node.
     */
    std::shared_ptr<ast_node_impl_t> top_node() const;

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
