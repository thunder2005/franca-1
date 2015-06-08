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

class type_collection_t final: public state_t
{
    DECL_PARSER_STATE_CTR(type_collection_t)
    DECL_PARSER_SUBSTATES(expect_type_collection_name,
                          expect_open_brace,
                          expect_optional_version,
                          expect_types_or_close_brace)

public:
    /* virtual */ void handle_token() override;
    /* virtual */ void handle_eof() override;
};

} // namespace state
} // namespace franca
