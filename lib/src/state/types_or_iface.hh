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

class types_or_iface_t final: public state_t
{
    DECL_PARSER_STATE_CTR(types_or_iface_t)

public:
    /* virtual */ void handle_token() override;
};

} // namespace state
} // namespace franca
