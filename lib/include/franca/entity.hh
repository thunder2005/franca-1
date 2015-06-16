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

#define DECL_ENTITY(__class, __impl)                                           \
    private:                                                                   \
        friend class __impl;                                                   \
        explicit __class( const std::shared_ptr<__impl> &impl );               \
        const __impl *impl() const noexcept;

#define DEFINE_ENTITY(__class, __impl)                                         \
    franca::entity::__class::__class(                                          \
            const std::shared_ptr<franca::entity::__impl> &impl )              \
        : entity_t(impl) {}                                                    \
    const franca::entity::__impl *franca::entity::__class::impl() const noexcept\
    {                                  \
        return static_cast<__impl*>(m_impl.get());                         \
    }

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
