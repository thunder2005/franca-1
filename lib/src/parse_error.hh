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

void raise_not_implemented( const char *feature_id = nullptr );
void raise_unexpected_eof( const char *what_expected );
void raise_type_exists( const char *tname );
void raise_type_not_found( const char *tname );
void raise_arg_name_already_used( const char *aname );

} // namespace franca
