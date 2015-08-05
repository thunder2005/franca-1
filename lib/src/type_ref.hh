/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// local includes:
#include "input_context.hh"

// std includes:
#include <memory>

namespace franca {

class ast_node_impl_t;

class type_ref_t final
{
public:
    type_ref_t() = default;
    type_ref_t( const std::string &tname,
                const std::shared_ptr<ast_node_impl_t> &base_ast_node,
                const input_context_t &input_context ) noexcept;
    ~type_ref_t();

public:
    const std::string &tname() const noexcept { return m_tname; }

private:
    std::string m_tname;
    std::shared_ptr<ast_node_impl_t> m_base_ast_node;
    input_context_t m_input_context;
};

} // namespace franca
