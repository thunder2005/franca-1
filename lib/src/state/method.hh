/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// parent include:
#include "state.hh"

// std includes:
#include <vector>

namespace franca {
namespace state {

class argument_t;

class method_t final: public state_t
{
    DECL_PARSER_STATE_CTR(method_t)
    DECL_PARSER_SUBSTATES(expect_method_keyword,
                          expect_method_name,
                          expect_open_brace,
                          expect_close_brace,
                          expect_in_keyword,
                          expect_in_open_brace,
                          expect_in_types,
                          expect_out_keyword,
                          expect_out_open_brace,
                          expect_out_types)

public:
    /* virtual */ void handle_token() override;
    /* virtual */ void handle_eof() override;

private:
    std::string m_name;
};

} // namespace state
} // namespace franca
