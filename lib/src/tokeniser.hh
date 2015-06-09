/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// std includes:
#include <functional>
#include <vector>

namespace franca {

class tokeniser_t final
{
public:
    struct rule_t final
    {
        const char *token;
        std::function<void()> action;
    };

public:
    explicit tokeniser_t( const char *&input )
        : m_input(input)
    {
    }

public /* rules */:
    void exec_rules();

    tokeniser_t &add_rule( const char *token, std::function<void()> action )
    {
        m_rules.push_back({token, action});
        return *this;
    }

    template<typename T>
    tokeniser_t &add_rule_assign( const char *token, T &dst, const T &val )
    {
        return add_rule(token, [&dst, val]() { dst = val; });
    }

public /* generic parsers */:
    bool is_token( const char *token, bool is_mutable = false );
    void expect_token( const char *token );
    bool is_fqn( bool is_mutable = false );
    std::string read_fqn( const char *error_msg );
    std::uint32_t read_u32( const char *error_msg );

private:
    const char *&m_input;
    std::vector<rule_t> m_rules;
};

} // namespace franca
