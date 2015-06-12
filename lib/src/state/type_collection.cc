/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "type_collection.hh"

// local includes:
#include "ast.hh"
#include "tokeniser.hh"
#include "state/version.hh"
#include "state/typedef.hh"

static const char s_type_collection_name_expected_msg[] = "A type collection name is expected.";
static const char s_open_brace_expected_msg[] = "An openning brace is expected.";
static const char s_close_brace_expected_msg[] = "A closing brace is expected.";

using namespace franca;

void state::type_collection_t::handle_token()
{
    tokeniser_t tkn(m_input);

    switch ( m_subst ) {
    case subst_t::expect_type_collection_name:
        ast().start_type_collection(
                    tkn.read_fqn(s_type_collection_name_expected_msg));
        m_subst = subst_t::expect_open_brace;
        break;

    case subst_t::expect_open_brace:
        tkn.add_rule_assign("{", m_subst, subst_t::expect_optional_version);
        tkn.exec_rules();
        break;

    case subst_t::expect_optional_version:
        if ( tkn.is_token("version") ) {
            enter_substate<state::version_t>();
            break;
        }

        m_subst = subst_t::expect_types_or_close_brace;
        /* walk through */

    case subst_t::expect_types_or_close_brace:
        tkn.add_rule("}", [this]{ ast().pop_node(); leave_state(); });
        tkn.add_rule("typedef", [this]{ enter_substate<state::typedef_t>(); });
        tkn.exec_rules();
        break;
    }
}

void state::type_collection_t::handle_eof()
{
    switch ( m_subst ) {
    case subst_t::expect_type_collection_name:
        raise_unexpected_eof(s_type_collection_name_expected_msg);
        break;
    case subst_t::expect_open_brace:
        raise_unexpected_eof(s_open_brace_expected_msg);
        break;
    case subst_t::expect_optional_version:
    case subst_t::expect_types_or_close_brace:
        raise_unexpected_eof(s_close_brace_expected_msg);
        break;
    }
}
