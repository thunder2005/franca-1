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

class package_t final: public state_t
{
    DECL_PARSER_STATE_CTR(package_t)
    DECL_PARSER_SUBSTATES(expect_package_keyword,
                          expect_package_name)

public:
    /* virtual */ const char *handle_token() override;
    /* virtual */ void handle_eof() override;
};

} // namespace state
} // namespace franca
