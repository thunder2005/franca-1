/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

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
    log_t debug();
    log_t info();
    log_t warn();
    log_t error();
    log_t log();

private:
    void process_translation( const std::string &input_name );
    log_t formated_log();

private:
    std::shared_ptr<logger_t> m_logger;
    std::shared_ptr<input_factory_t> m_input_factory;
    std::stack<std::shared_ptr<translation_unit_t>> m_translation_units;
    std::shared_ptr<translation_unit_t> m_translation_unit;
};

} // namespace franca
