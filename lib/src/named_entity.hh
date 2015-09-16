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

class named_entity_t final
{
public:
    named_entity_t( const std::string &name,
                    const std::shared_ptr<entity_impl_t> &entity ) noexcept
        : m_name(name)
        , m_entity(entity)
    {
    }

public:
    const std::string &name() const noexcept { return m_name; }
    const std::shared_ptr<entity_impl_t> &entity() const noexcept { return m_entity; }

private:
    std::string m_name;
    std::shared_ptr<entity_impl_t> m_entity;
};

} // namespace franca
