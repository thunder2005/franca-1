/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// std includes:
#include <memory>
#include <vector>

namespace franca {

class ast_visitor_t;
class input_factory_t;
class logger_t;
class parser_impl_t;

namespace entity {
class package_t;
} // namespace entity

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
     * \brief Set an input factory.
     * \param input Input factory.
     * \sa franca::input_factory_t
     */
    void set_input_factory( const std::shared_ptr<input_factory_t> &factory );

    /*!
     * \brief Parse an input.
     * \return True, if the pasre was successful.
     */
    bool parse() noexcept;

#if 0
    /*!
     * \brief Visit all AST nodes (DFS algorithm).
     * \param visitor AST visitor class.
     *
     * Apply the given AST visitor class to every node in AST. This function
     * starts at a root node and uses a depth-first-search approach.
     */
    void visit_all_dfs( ast_visitor_t &visitor ) const;
#endif

private:
    std::unique_ptr<parser_impl_t> m_impl;
};

} // namespace franca
