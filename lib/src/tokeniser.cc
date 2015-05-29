/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "tokeniser.hh"

// local includes:
#include "parse_error.hh"

using namespace franca;

template<typename T, typename F>
static std::string listify( const std::vector<T> &items, const F &func )
{
    std::string ret;
    bool is_first = true;
    for ( const auto &item : items ) {
        if ( !is_first )
            ret += ", ";
        is_first = false;
        ret += func(item);
    }
    return ret;
}

void tokeniser_t::exec_rules()
{
    for ( const auto &rule : m_rules ) {
        if ( is_token(rule.token, true) ) {
            rule.action();
            return;
        }
    }

    const std::string error_msg = "One of these tokens is expected: " +
            listify(m_rules, []( const rule_t &rule ){ return rule.token; }) + ".";
    throw parse_error_t(error_msg);
}

bool tokeniser_t::is_token( const char *token, bool is_mutable )
{
    const char *input = m_input;

    while ( *input && *token ) {
        if ( *(input++) != *(token++) )
            return false;
    }

    const bool is_valid_token = !(*token || std::isalnum(*input));
    if ( is_valid_token && is_mutable )
        m_input = input;
    return is_valid_token;
}

bool tokeniser_t::is_fqn( bool is_mutable )
{
    const char *input = m_input;

    while ( 42 ) {
        // first symbol should be a letter:
        if ( !std::isalpha(*input) )
            return false;

        // the rest can be digits or letters:
        while ( std::isalnum(*(++input)) );

        // it may contain a dot:
        if ( *input != '.' )
            break;
        input++;
    }

    const bool is_valid_fqn = !std::isalnum(*input);
    if ( is_valid_fqn && is_mutable )
        m_input = input;
    return is_valid_fqn;
}

std::string tokeniser_t::read_fqn( const char *error_msg )
{
    const char *orig_input = m_input;

    if ( !is_fqn(true) )
        throw parse_error_t(std::string("Invalid FQN. ") + error_msg);

    return std::string(orig_input, m_input - orig_input);
}
