/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "tokeniser.hh"

// local includes:
#include "parse_error.hh"

// std includes:
#include <cerrno>
#include <limits>

using namespace franca;

namespace {

bool is_token_separator( char c )
{
    switch ( c ) {
    case 0:
    case ' ':
    case '\t':
    case '{':
    case '}':
        return true;
    }
    return false;
}

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

template<typename T, bool = std::is_signed<T>()>
struct strtox_traits_t
{
    using type = long long;
    static type parse_func( const char *str, char **endp )
    {
        return std::strtoll(str, endp, 0);
    }
};

template<typename T>
struct strtox_traits_t<T, false>
{
    using type = unsigned long long;
    static type parse_func( const char *str, char **endp )
    {
        return std::strtoull(str, endp, 0);
    }
};


template<typename T>
T read_int( const char *&input, const char *error_msg )
{
    static_assert(std::is_integral<T>(), "this function is for integral types only");
    errno = 0;

    char *endp;
    auto value = strtox_traits_t<T>::parse_func(input, &endp);

    if ( (errno != 0) ||               /* conversion error */
         (endp == input) ||            /* no digits found */
         !is_token_separator(*endp) || /* there is no token separator after */
         (value < std::numeric_limits<T>::min()) ||
         (value > std::numeric_limits<T>::max()) ) {
        throw parse_error_t(std::string("Invalid integer. ") + error_msg);
    }

    input = endp;
    return static_cast<T>(value);
}

} // anonymous namespace

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

    const bool is_valid_token = !*token && is_token_separator(*input);
    if ( is_valid_token && is_mutable )
        m_input = input;
    return is_valid_token;
}

void tokeniser_t::expect_token( const char *token )
{
    if ( !is_token(token, true) )
        throw parse_error_t(std::string("This token expected: ") + token);
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

    const bool is_valid_fqn = is_token_separator(*input);
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

bool tokeniser_t::is_typename( bool is_mutable )
{
    const char *input = m_input;

    // first symbol should be a letter:
    if ( !std::isalpha(*input) )
        return false;

    // the rest can be digits or letters:
    while ( std::isalnum(*(++input)) );

    const bool is_valid_typename = is_token_separator(*input);
    if ( is_valid_typename && is_mutable )
        m_input = input;
    return is_valid_typename;
}

std::string tokeniser_t::read_typename( const char *error_msg )
{
    const char *orig_input = m_input;

    if ( !is_typename(true) )
        throw parse_error_t(std::string("Invalid type name. ") + error_msg);

    return std::string(orig_input, m_input - orig_input);
}

std::uint32_t tokeniser_t::read_u32( const char *error_msg )
{
    return read_int<std::uint32_t>(m_input, error_msg);
}
