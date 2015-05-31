/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// std includes:
#include <string>

namespace franca {

class parser_impl_t;
class state_t;

class ast_t final
{
public:
    explicit ast_t( parser_impl_t &parser );
    ast_t( const ast_t & ) = delete;
    ast_t &operator=( const ast_t & ) = delete;

public:
    void set_active_package( const std::string &fqn );

private:
    parser_impl_t &m_parser;
};

} // namespace franca
