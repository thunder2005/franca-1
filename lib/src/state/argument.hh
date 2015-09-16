/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// parent include:
#include "state.hh"

namespace franca {

namespace entity {
class type_impl_t;
} // namespace entity

namespace state {

class argument_t final: public state_t
{
    DECL_PARSER_STATE_CTR(argument_t)
    DECL_PARSER_SUBSTATES(expect_typename,
                          expect_argument_name)

public:
    /* virtual */ void handle_token() override;
    /* virtual */ void handle_eof() override;

private:
    void finalise_argument( const std::string &name );

private:
    std::string m_given_typename;
    std::shared_ptr<entity::type_impl_t> m_type;
};

} // namespace state
} // namespace franca
