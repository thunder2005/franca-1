/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "interface.hh"

// local includes:
#include "ast.hh"
#include "tokeniser.hh"
#include "state/version.hh"
#include "state/method.hh"

using namespace franca;

void state::interface_t::handle_token()
{
    tokeniser_t tkn(m_input);

    switch ( m_subst ) {
    case subst_t::expect_interface_name:
        ast().start_interface(
                    tkn.read_fqn("An interface name is expected."));
        m_subst = subst_t::expect_open_brace;
        break;

    case subst_t::expect_open_brace:
        tkn.expect_token("{");
        m_subst = subst_t::expect_version;
        break;

    case subst_t::expect_version:
        m_subst = subst_t::expect_attribute;
        if ( tkn.is_token("version") ) {
            enter_substate<state::version_t>();
            break;
        }
        /* walk through */

    case subst_t::expect_attribute:
        if ( tkn.is_token("attribute") ) {
            raise_not_implemented("attribute");
            break;
        }
        m_subst = subst_t::expect_method;
        /* walk through */

    case subst_t::expect_method:
        if ( tkn.is_token("method") ) {
            enter_substate<state::method_t>();
            break;
        }
        m_subst = subst_t::expect_broadcast;
        /* walk through */

    case subst_t::expect_broadcast:
        if ( tkn.is_token("broadcast") ) {
            raise_not_implemented("broadcast");
            break;
        }
        m_subst = subst_t::expect_close_brace;
        /* walk through */

    case subst_t::expect_close_brace:
        tkn.expect_token("}");
        leave_state();
        break;
    }
}

void state::interface_t::handle_eof()
{
    raise_unexpected_eof("A valid interface definition is expected.");
}
