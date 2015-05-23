/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// std includes:
#include <stdexcept>

namespace franca {

class parse_error_t: public std::runtime_error
{
    using runtime_error::runtime_error;
};

} // namespace franca
