/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "state.hh"

// local includes:
#include "log.hh"
#include "stm.hh"
#include "parser_impl.hh"
#include "parse_error.hh"

using namespace franca;

class input_line_updater_t final
{
public:
    input_line_updater_t( input_line_t &input, const char *&local_copy )
        : m_orig_input(input.mutable_data())
        , m_local_copy(local_copy)
    {
        m_local_copy = m_orig_input;
    }

    ~input_line_updater_t()
    {
        m_orig_input = m_local_copy;
    }

private:
    const char *&m_orig_input;
    const char *&m_local_copy;
};

state_t::state_t( const char *name, stm_t &stm )
    : m_input(nullptr)
    , m_name(name)
    , m_stm(stm)
    , m_transition_occurred(false)
{
}

void state_t::handle_token( input_line_t &input )
{
    /* Ensure that we update a data pointer in an input line before leaving
     * this function. For the sake of exception safety! */
    input_line_updater_t updater(input, m_input);

    /* Here we skip spaces, comments and other irrelevant stuff and go to a
     * token which should be processed. */
    goto_next_token();

    /* Call an implementation of the token handler of the specific state. */
    if ( !input.is_eol() ) {
        auto orig_input = m_input;
        handle_token();

        /* If we did not advance at least one character AND no state transition
         * was done, then we have an issue in STM, which leads to an infinite loop.
         * This check prevents looping forever. */
        if ( (m_input == orig_input) && !m_transition_occurred ) {
            throw parse_error_t("Internal error: infinite loop detected.");
        }
    }
}

void state_t::handle_eof()
{
    /* default implementation does nothing */
}

void state_t::goto_next_token()
{
    while ( std::isspace(*m_input) )
        m_input++;
}

void state_t::handle_token()
{
    /* default implementation throws an exception */
    raise_not_implemented();
}

ast_t &state_t::ast()
{
    return m_stm.ast();
}

log_t state_t::debug()
{
    return m_stm.parser().debug();
}

log_t state_t::info()
{
    return m_stm.parser().info();
}

log_t state_t::warn()
{
    return m_stm.parser().warn();
}

log_t state_t::error()
{
    return m_stm.parser().error();
}

void state_t::transit( const std::shared_ptr<state_t> &new_state ) noexcept
{
    m_transition_occurred = true;
    m_stm.simple_transit(new_state);
}

void state_t::enter_substate( const std::shared_ptr<state_t> &new_state ) noexcept
{
    m_transition_occurred = true;
    m_stm.push_transit(new_state);
}

void state_t::leave_state() noexcept
{
    m_transition_occurred = true;
    m_stm.pop_transit();
}

void state_t::raise_not_implemented( const char *feature_id ) const
{
    if ( feature_id ) {
        throw parse_error_t(std::string("Internal error: feature not implemented: ") +
                            feature_id + ".");
    } else {
        throw parse_error_t("Internal error: feature not implemented.");
    }
}

void state_t::raise_unexpected_eof( const char *what_expected ) const
{
    if ( what_expected ) {
        throw parse_error_t(std::string("Got EOF. ") + what_expected);
    } else {
        throw parse_error_t("Unexpected EOF.");
    }
}
