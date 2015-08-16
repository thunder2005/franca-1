/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

namespace franca {
namespace entity {
namespace attr {

/*!
 * \brief Size of an integer type.
 */
enum class integer_size_t
{
    int_8,  //!< 8 bit integer.
    int_16, //!< 16 bit integer.
    int_32, //!< 32 bit integer.
    int_64  //!< 64 bit integer.
};

} // namespace attr
} // namespace entity
} // namespace franca
