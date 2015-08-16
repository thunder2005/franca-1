/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "argument.hh"

// local includes:
#include "ast.hh"
#include "tokeniser.hh"
#include "log.hh"

using namespace franca;

void state::argument_t::handle_token()
{
    tokeniser_t tkn(m_input);

    switch ( m_subst ) {
    case subst_t::expect_typename:
        m_type_ref = { tkn.read_fqn("A type of an argument is expected."),
                       ast().top_node(), input_context() };
        m_subst = subst_t::expect_argument_name;
        break;

    case subst_t::expect_argument_name:
        m_argument_name = tkn.read_typename("A name of an argument is expected.");
        debug() << "Argument:" << m_argument_name << "of type" << m_type_ref.tname();
        leave_state();
        break;
    }
}

void state::argument_t::handle_eof()
{
    raise_unexpected_eof("A valid method argument is expected.");
}
