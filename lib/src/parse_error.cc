/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "parse_error.hh"

namespace franca {

void raise_not_implemented( const char *feature_id )
{
    if ( feature_id ) {
        throw parse_error_t(std::string("Internal error: feature not implemented: ") +
                            feature_id + ".");
    } else {
        throw parse_error_t("Internal error: feature not implemented.");
    }
}

void raise_unexpected_eof( const char *what_expected )
{
    if ( what_expected ) {
        throw parse_error_t(std::string("Got EOF. ") + what_expected);
    } else {
        throw parse_error_t("Unexpected EOF.");
    }
}

void raise_type_exists( const char *tname )
{
    throw parse_error_t(std::string("Type '") + tname + "` already exists.");
}

void raise_type_not_found( const char *tname )
{
    throw parse_error_t(std::string("Type '") + tname + "` is not found.");
}

void raise_arg_name_already_used( const char *aname )
{
    throw parse_error_t(std::string("An argument name '") + aname +
                        "` is already used.");
}

} // namespace franca
