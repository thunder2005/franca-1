/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// std includes:
#include <memory>
#include <string>
#include <vector>

namespace franca {

class input_provider_t;

/*!
 * \brief Abstract input factory.
 *
 * This class defines an interface to an input backend. Implementations of
 * specific input backends, e.g. an input from file, should derive from this
 * class. An active backend is set via \ref franca::parser_t::set_input_factory().
 *
 * The factory produces dedicated input providers for different input names.
 * This is required in order to support multiple input sources and imports in
 * *.fidl files.
 */
class input_factory_t
{
public:
    //! Virtual destructor.
    virtual ~input_factory_t() = default;

public:
    /*!
     * \brief Get a list of input names.
     * \return A list of normalised input names.
     *
     * This method returns a list of input names (e.g. filenames) to be parsed.
     * This is, for instance, a list of arguments provided to a command-line tool.
     */
    virtual std::vector<std::string> input_names() const noexcept = 0;

    /*!
     * \brief Create an input by its name.
     * \param norm_name Normalised input name.
     * \return An new instance of an input for a given name.
     *
     * This method creates an input object for a provided normalised input name.
     * The input object shall be used to access the data.
     *
     * If an input cannot be created, this method resurns a null pointer.
     */
    virtual std::unique_ptr<input_provider_t> create_input(
            const std::string &norm_name ) const noexcept = 0;

    /*!
     * \brief Normalise an input name.
     * \param name Input name.
     * \return A normalised input name.
     *
     * This method normalises a given input name. For example, if the factory
     * provides an access to the local filesystem, then this method shall convert
     * relative paths to absolute ones. Normalised input names are used in
     * \ref create_input().
     */
    virtual std::string normalise_name( const std::string &name ) const noexcept = 0;
};

} // namespace franca
