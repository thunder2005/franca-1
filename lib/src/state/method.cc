/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "method.hh"

// local includes:
#include "ast.hh"
#include "tokeniser.hh"
#include "parse_error.hh"
#include "state/argument.hh"

using namespace franca;

void state::method_t::handle_token()
{
    tokeniser_t tkn(m_input);

    switch ( m_subst ) {
    case subst_t::expect_method_keyword:
        tkn.expect_token("method");
        m_subst = subst_t::expect_method_name;
        break;

    case subst_t::expect_method_name:
        m_name = tkn.read_typename("A method name is expected.");
        m_subst = subst_t::expect_open_brace;
        break;

    case subst_t::expect_open_brace:
        tkn.expect_token("{");
        m_subst = subst_t::expect_in_keyword;
        break;

    case subst_t::expect_in_keyword:
        if ( tkn.is_token("in", true) ) {
            m_subst = subst_t::expect_in_open_brace;
            break;
        }
        m_subst = subst_t::expect_out_keyword;
        /* walk through */

    case subst_t::expect_out_keyword:
        if ( tkn.is_token("out", true) ) {
            m_subst = subst_t::expect_out_open_brace;
            break;
        }
        m_subst = subst_t::expect_close_brace;
        /* walk through */

    case subst_t::expect_close_brace:
        tkn.expect_token("}");
        leave_state();
        break;

    case subst_t::expect_in_open_brace:
        tkn.expect_token("{");
        m_subst = subst_t::expect_in_types;
        break;

    case subst_t::expect_in_types:
        if ( tkn.is_token("}", true) ) {
            m_subst = subst_t::expect_out_keyword;
        } else {
            enter_substate<argument_t>();
        }
        break;

    case subst_t::expect_out_open_brace:
        tkn.expect_token("{");
        m_subst = subst_t::expect_out_types;
        break;

    case subst_t::expect_out_types:
        if ( tkn.is_token("}", true) ) {
            m_subst = subst_t::expect_close_brace;
        } else {
            enter_substate<argument_t>();
        }
        break;
    }
}

void state::method_t::handle_eof()
{
    raise_unexpected_eof("A valid method definition is expected.");
}
