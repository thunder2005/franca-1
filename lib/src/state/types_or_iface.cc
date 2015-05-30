/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "types_or_iface.hh"

// local includes:
#include "tokeniser.hh"

static const char s_type_collection_name_expected_msg[] = "A type collection name is expected.";
static const char s_interface_name_expected_msg[] = "An interface name is expected.";

using namespace franca;

void state::types_or_iface_t::handle_token()
{
    tokeniser_t tkn(m_input);

    switch ( m_subst ) {
    case subst_t::expect_types_or_iface_keyword:
        tkn.add_rule_assign("typeCollection", m_subst, subst_t::expect_type_collection_name);
        tkn.add_rule_assign("interface", m_subst, subst_t::expect_interface_name);
        tkn.exec_rules();
        break;

    case subst_t::expect_type_collection_name:
    case subst_t::expect_interface_name:
        raise_not_implemented();
        break;
    }
}

void state::types_or_iface_t::handle_eof()
{
    switch ( m_subst ) {
    case subst_t::expect_types_or_iface_keyword:
        /* We are not inside a type collection or an interface definition.
         * It is okay to end a file here. */
        break;
    case subst_t::expect_type_collection_name:
        raise_unexpected_eof(s_type_collection_name_expected_msg);
        break;
    case subst_t::expect_interface_name:
        raise_unexpected_eof(s_interface_name_expected_msg);
        break;
    }
}
