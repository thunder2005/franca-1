/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// std includes:
#include <string>
#include <iosfwd>

namespace franca {

/*!
 * \brief Abstract input provider.
 *
 * This class defines an interface to an input backend. Implementations of
 * specific input backends, e.g. an input from file, should derive from this
 * class. Specific input providers are created by
 * \ref franca::input_factory_t::create_input().
 */
class input_provider_t
{
public:
    //! Virtual destructor.
    virtual ~input_provider_t() = default;

public:
    /*!
     * \brief Get a full name of the provider.
     * \return A full name of the provider.
     *
     * This method should return a name of this provider. It shall be used for
     * debugging purposes and output. For instance, for a file input backend it
     * might return a full filename.
     */
    virtual const std::string &name() const noexcept = 0;

    /*!
     * \brief Get a short name of the provider.
     * \return A short name of the provider.
     *
     * This is a short version of \ref name(). For example, it may contain just a
     * filename without a full path.
     */
    virtual const std::string &short_name() const noexcept = 0;

    /*!
     * \brief Get an associated input stream.
     * \return An input stream.
     *
     * This method should return an input stream associated with this provider.
     */
    virtual std::istream &stream() noexcept = 0;
};

} // namespace franca
