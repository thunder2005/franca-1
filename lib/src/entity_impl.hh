/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// std includes:
#include <memory>

#define DECL_FRANCA_ENTITY_IMPL_WARGS(__iface, __impl, ...)                    \
    public:                                                                    \
        static std::shared_ptr<__impl> create( __VA_ARGS__ );                  \
        explicit __impl( private_ctr, __VA_ARGS__ );                           \
        __iface interface() noexcept;                                          \
        void accept_visitor( ast_visitor_t &visitor ) override;

#define DECL_FRANCA_ENTITY_IMPL(__iface, __impl)                               \
    public:                                                                    \
        static std::shared_ptr<__impl> create();                               \
        explicit __impl( private_ctr );                                        \
        __iface interface() noexcept;                                          \
        void accept_visitor( ast_visitor_t &visitor ) override;

#define DEFINE_FRANCA_ENTITY_IMPL(__iface, __impl)                             \
    franca::entity::__iface franca::entity::__impl::interface() noexcept       \
    {                                                                          \
        return __iface(std::static_pointer_cast<__impl>(shared_from_this()));  \
    }                                                                          \
    void franca::entity::__impl::accept_visitor( ast_visitor_t &visitor )      \
    {                                                                          \
        visitor.visit(interface());                                            \
    }

namespace franca {

class ast_node_impl_t;
class ast_visitor_t;

class entity_impl_t
{
public:
    //! Virtual destructor.
    virtual ~entity_impl_t() = default;

public:
    //! \internal
    entity_impl_t( const entity_impl_t & ) = delete;
    //! \internal
    entity_impl_t &operator=( const entity_impl_t & ) = delete;

public:
    /*!
     * \brief Check if this enity is associated with an AST node.
     * \return True, if the entity is associated with an AST node.
     */
    bool has_ast_node() const noexcept;

    /*!
     * \brief Get an associated AST node.
     * \return AST node for this entity.
     */
    std::shared_ptr<ast_node_impl_t> ast_node() const noexcept;

public:
    virtual void apply_version( std::uint32_t major, std::uint32_t minor );
    virtual void accept_visitor( ast_visitor_t &visitor ) = 0;

protected:
    //! \internal
    class private_ctr {};
    //! \internal
    entity_impl_t() = default;

private:
    friend class ast_node_impl_t; // see ast_node_impl_t::bind_entity()
    std::weak_ptr<ast_node_impl_t> m_ast_node;
};

} // namespace franca
