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

class version_t final: public state_t
{
    DECL_PARSER_STATE_CTR(version_t)
    DECL_PARSER_SUBSTATES(expect_version_keyword,
                          expect_open_brace,
                          expect_major_keyword,
                          expect_major_number,
                          expect_minor_keyword,
                          expect_minor_number,
                          expect_close_brace)

public:
    /* virtual */ void handle_token() override;
    /* virtual */ void handle_eof() override;

private:
    std::uint32_t m_major = 0;
    std::uint32_t m_minor = 0;
};

} // namespace state
} // namespace franca
