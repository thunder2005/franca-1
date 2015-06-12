/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// parent include:
#include "state.hh"

namespace franca {
namespace state {

class typedef_t final: public state_t
{
    DECL_PARSER_STATE_CTR(typedef_t)
    DECL_PARSER_SUBSTATES(expect_new_typename,
                          expect_is_keyword,
                          expect_existing_typename)

public:
    /* virtual */ void handle_token() override;
    /* virtual */ void handle_eof() override;

private:
    std::string m_new_typename;
};

} // namespace state
} // namespace franca
