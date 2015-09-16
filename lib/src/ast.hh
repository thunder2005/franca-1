/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// local includes:
#include "loggable.hh"
#include "ast_flags.hh"

// std includes:
#include <string>
#include <memory>
#include <stack>
#include <map>

namespace franca {

class parser_impl_t;
class ast_node_impl_t;
class entity_impl_t;

namespace entity {
class package_impl_t;
class type_impl_t;
} // namespace entity

/*!
 * \brief Abstract syntax tree.
 */
class ast_t final
        : public loggable_t
{
public:
    explicit ast_t( const loggable_t &loggable );
    ast_t( const ast_t & ) = delete;
    ast_t &operator=( const ast_t & ) = delete;

public:
    void set_active_package( const std::string &fqn );

    const std::shared_ptr<entity::package_impl_t> &active_package() const noexcept
    {
        return m_active_package;
    }

    void start_type_collection( const std::string &fqn );
    void start_interface( const std::string &fqn );

    void add_type( const std::string &fqn, const std::shared_ptr<entity::type_impl_t> &type );
    std::shared_ptr<entity::type_impl_t> type( const std::string &fqn ) noexcept;

    std::shared_ptr<entity::type_impl_t> existing_type( const std::string &fqn );

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
            node_at( const std::string &fqn, ast_flags_t flags = ast_flags_t() ) noexcept;

    /*!
     * \brief Get a current top node.
     * \return Current AST node.
     */
    const std::shared_ptr<ast_node_impl_t> &top_node() const;

    /*!
     * \brief Get an entity of a current top node.
     * \return Entity associated with the top node.
     */
    const std::shared_ptr<entity_impl_t> &top_entity() const;

    /*!
     * \brief Restore a previous top node.
     */
    void pop_node();

    /*!
     * \brief Get a root node.
     * \return Root node.
     */
    std::shared_ptr<ast_node_impl_t> root_node() const;

private:
    std::shared_ptr<ast_node_impl_t> m_root;
    std::stack<std::shared_ptr<ast_node_impl_t>> m_node_stack;

private:
    std::shared_ptr<entity::package_impl_t> m_active_package;
    std::map<std::string, std::shared_ptr<entity::type_impl_t>> m_predefined_types;
};

} // namespace franca
