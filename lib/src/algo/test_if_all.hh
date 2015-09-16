/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// std includes:
#include <algorithm>

namespace franca {
namespace algo {

//! \internal
template<typename Test>
bool test_if_all( const Test & /*test*/ )
{
    return false;
}

/*!
 * \brief Run a test on all containers.
 *
 * This function accepts a test (a predicate), which will be executed on
 * all provided STL containers. The function returns true if at least one
 * test succeeds.
 */
template<typename Test, typename Head, typename... Tail>
bool test_if_all( const Test &test, const Head &head, const Tail&... tail )
{
    auto it = std::find_if(head.cbegin(), head.cend(), test);
    if ( it == head.cend() ) { /* == not found */
        return test_if_all(test, tail...);
    }
    return true;
}

} // namespace algo
} // namespace franca
