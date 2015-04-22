/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// std includes:
#include <iosfwd>
#include <memory>

namespace franca {

class logger_t;
class parser_impl_t;

/*!
 * \brief Franca IDL parser.
 *
 * This class implements a Franca IDL parser.
 */
class parser_t final
{
public:
    /*!
     * \brief Create a Franca IDL parser.
     */
    parser_t();

    //! Destructor.
    ~parser_t();

public:
    void set_logger( std::unique_ptr<logger_t> &logger );

private:
    std::unique_ptr<parser_impl_t> m_impl;
};

} // namespace franca
