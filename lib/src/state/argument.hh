/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// parent include:
#include "state.hh"

// local includes:
#include "type_ref.hh"

namespace franca {
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
    type_ref_t m_type_ref;
    std::string m_argument_name;
};

} // namespace state
} // namespace franca
