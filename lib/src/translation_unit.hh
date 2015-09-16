/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// local includes:
#include "loggable.hh"

// std includes:
#include <memory>
#include <iosfwd>

namespace franca {

class ast_t;
class input_context_t;
class input_provider_t;
class log_t;
class parser_impl_t;
class stm_t;

/*!
 * \brief Translation unit.
 *
 * This class represents a translation unit, i.e. a single *.fidl file.
 */
class translation_unit_t final
        : public loggable_t
{
public:
    translation_unit_t(
            parser_impl_t &parser,
            std::unique_ptr<input_provider_t> &&input_provider );
    ~translation_unit_t();

    translation_unit_t( const translation_unit_t & ) = delete;
    translation_unit_t &operator=( const translation_unit_t & ) = delete;

public:
    input_context_t input_context() const noexcept;
    log_t formated_log() const noexcept;

public:
    void process_input();

private:
    void process_line( const char *line );

private:
    parser_impl_t &m_parser;
    std::unique_ptr<input_provider_t> m_input_provider;

    const std::string &m_input_name;
    std::size_t m_line_nr = 0; //!< Line number.
    std::size_t m_char_nr = 0; //!< Character number.

    std::unique_ptr<ast_t> m_ast; //!< Abstract syntax tree.
    std::unique_ptr<stm_t> m_stm; //!< Parsing state machine.
};

} // namespace franca
