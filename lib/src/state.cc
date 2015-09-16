/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "state.hh"

// local includes:
#include "input_context.hh"
#include "input_cursor.hh"
#include "log.hh"
#include "parse_error.hh"
#include "stm.hh"
#include "translation_unit.hh"

using namespace franca;

state_t::state_t( const char *name, stm_t &stm )
    : loggable_t(stm)
    , m_input(nullptr)
    , m_name(name)
    , m_stm(stm)
    , m_transition_occurred(false)
{
}

void state_t::handle_token( input_cursor_t &input_cursor )
{
    /* Ensure that we update a data pointer in an input line before leaving
     * this function. For the sake of exception safety! */
    input_cursor_updater_t updater(input_cursor, m_input);

    /* Here we skip spaces, comments and other irrelevant stuff and go to a
     * token which should be processed. */
    goto_next_token();

    /* Call an implementation of the token handler of the specific state. */
    if ( *m_input != '\0' ) {
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

input_context_t state_t::input_context() noexcept
{
    return m_stm.tu().input_context();
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

void state_t::leave_state()
{
    m_transition_occurred = true;
    m_stm.pop_transit();

    if ( m_finaliser ) {
        m_finaliser();
    }
}
