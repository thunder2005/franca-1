/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// parent include:
#include "entity/type_impl.hh"

// franca includes:
#include "franca/entity/integer_size.hh"

namespace franca {
namespace entity {

class integer_t;

class integer_impl_t final
        : public type_impl_t
        , public std::enable_shared_from_this<integer_impl_t>
{
public:
    /*!
     * \brief Create an integer type entity.
     * \param is_signed True, if it is a signed integer.
     * \param size Size of this integer type.
     * \return A shared pointer to a constructed entity.
     *
     * This function constructs an integer type entity.
     */
    static std::shared_ptr<integer_impl_t> create( bool is_signed, integer_size_t size );

    //! \internal
    explicit integer_impl_t( private_ctr, bool is_signed, integer_size_t size );

public:
    //! Create a public interface object.
    integer_t interface() noexcept;

public:
    bool is_signed() const noexcept;
    integer_size_t size() const noexcept;

private:
    bool m_is_signed;
    integer_size_t m_size;
};

} // namespace entity
} // namespace franca
