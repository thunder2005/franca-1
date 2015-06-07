/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// std includes:
#include <memory>

namespace franca {

class ast_node_t;
class entity_impl_t;

class entity_t
{
public:
    //! Virtual destructor.
    virtual ~entity_t() = default;

public:
    /*!
     * \brief Get a fully qualified name of this entity.
     * \return An FQN.
     */
    std::string fqn() const noexcept;

    /*!
     * \brief Get an AST node associated with this entity.
     * \return An associated AST node.
     */
    ast_node_t ast_node() const noexcept;

protected:
    //! \internal
    explicit entity_t( const std::shared_ptr<entity_impl_t> &impl )
        : m_impl(impl)
    {
    }

protected:
    std::shared_ptr<entity_impl_t> m_impl;
};

} // namespace franca
