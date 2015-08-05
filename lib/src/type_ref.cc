/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "type_ref.hh"

using namespace franca;

type_ref_t::type_ref_t( const std::string &tname,
                        const std::shared_ptr<ast_node_impl_t> &base_ast_node,
                        const input_context_t &input_context ) noexcept
    : m_tname(tname)
    , m_base_ast_node(base_ast_node)
    , m_input_context(input_context)
{
}

type_ref_t::~type_ref_t()
{
}
