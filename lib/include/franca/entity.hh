/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// std includes:
#include <memory>

namespace franca {

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

protected:
    std::shared_ptr<entity_impl_t> m_impl;
};

} // namespace franca
