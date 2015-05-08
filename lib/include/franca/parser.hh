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
class input_provider_t;
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
    /*!
     * \brief Set a logger backend.
     * \param logger Logger.
     * \sa franca::logger_t
     */
    void set_logger( const std::shared_ptr<logger_t> &logger );

    /*!
     * \brief Set an input provider.
     * \param input Input provider.
     * \sa franca::input_provider_t
     */
    void set_input_provider( const std::shared_ptr<input_provider_t> &input );

    /*!
     * \brief Parse an input.
     * \return True, if the pasre was successful.
     */
    bool parse();

private:
    std::unique_ptr<parser_impl_t> m_impl;
};

} // namespace franca
