/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// local includes:
#include "loggable_impl.hh"

// std includes:
#include <memory>
#include <vector>
#include <stack>

namespace franca {

class ast_visitor_t;
class input_context_t;
class input_factory_t;
class logger_t;
class log_t;
class translation_unit_t;

namespace entity {
class package_impl_t;
} // namespace entity

class parser_impl_t final
        : public loggable_impl_t
{
public:
    parser_impl_t();
    ~parser_impl_t();

public:
    parser_impl_t( const parser_impl_t & ) = delete;
    parser_impl_t &operator=( const parser_impl_t & ) = delete;

public:
    void set_logger( const std::shared_ptr<logger_t> &logger );
    void set_input_factory( const std::shared_ptr<input_factory_t> &factory );
    bool parse() noexcept;

#if 0
    void visit_all_dfs( ast_visitor_t &visitor ) const;
#endif

public:
    input_context_t input_context() const noexcept;

    /* virtual */ log_t debug() const noexcept override;
    /* virtual */ log_t info() const noexcept override;
    /* virtual */ log_t warn() const noexcept override;
    /* virtual */ log_t error() const noexcept override;

    log_t raw_log() const noexcept;
    log_t formated_log() const noexcept;

private:
    void process_translation( const std::string &input_name );


private:
    std::shared_ptr<logger_t> m_logger;
    std::shared_ptr<input_factory_t> m_input_factory;
    std::stack<std::shared_ptr<translation_unit_t>> m_translation_units;
    std::shared_ptr<translation_unit_t> m_translation_unit;
};

} // namespace franca
