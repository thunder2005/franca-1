/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// std includes:
#include <cstdlib>

namespace franca {

class stm_t final
{
public:
    std::size_t handle_token( const char *token );
    void handle_eof();
};

} // namespace franca
