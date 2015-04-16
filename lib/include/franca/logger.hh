/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// std includes:
#include <iosfwd>

namespace franca {

/*!
 * \brief Abstract logger.
 *
 * This class defines an interface to a logging backend. Implementations of
 * specific logging backends should derive from this class. An active backend
 * is set via \ref franca::parser_t::set_logger().
 */
class logger_t
{
public:
    //! Virtual destructor.
    virtual ~logger_t() = default;

public:
    /*!
     * \brief Print a log message.
     * \param stream Log message.
     *
     * This method should perform an actual log print-out.
     */
    virtual void print( std::ostringstream &stream ) noexcept = 0;
};

} // namespace franca
