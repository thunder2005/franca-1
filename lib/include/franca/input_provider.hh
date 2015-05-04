/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// std includes:
#include <string>

namespace franca {

/*!
 * \brief Abstract input provider.
 *
 * This class defines an interface to an input backend. Implementations of
 * specific input backends, e.g. an input from file, should derive from this
 * class. An active backend is set via \ref franca::parser_t::set_input_provider().
 */
class input_provider
{
public:
    //! Virtual destructor.
    virtual ~input_provider() = default;

public:
    /*!
     * \brief Get a name of the provider.
     * \return A name of the provider.
     *
     * This method should return a name of this provider. It shall be used for
     * debugging purposes and output. For instance, for a file input backend it
     * might return a filename.
     */
    std::string name() const noexcept = 0;

    /*!
     * \brief Read a next line.
     * \return A next line of the input.
     *
     * This methods reads a next line of the input. The line should not contain
     * EOL characters. In case of EOF, an empty string should be returned. In
     * event of I/O error, exceptions should be thrown.
     */
    std::string next_line() = 0;

    /*!
     * \brief Check if EOF condition is met.
     * \return True, if end of file is reached.
     */
    bool is_eof() const noexcept = 0;
};

} // namespace franca
