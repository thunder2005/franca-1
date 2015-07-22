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

class interface_t final: public state_t
{
    DECL_PARSER_STATE_CTR(interface_t)
    DECL_PARSER_SUBSTATES(expect_interface_name,
                          expect_open_brace,
                          expect_version,
                          expect_attribute,
                          expect_method,
                          expect_broadcast,
                          expect_close_brace)

public:
    /* virtual */ void handle_token() override;
    /* virtual */ void handle_eof() override;
};

} // namespace state
} // namespace franca
