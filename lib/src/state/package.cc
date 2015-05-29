/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "package.hh"

// local includes:
#include "tokeniser.hh"

static const char s_package_name_expected_msg[] = "A package name is expected.";

using namespace franca;

void state::package_t::handle_token()
{
    tokeniser_t tkn(m_input);

    switch ( m_subst ) {
    case subst_t::expect_package_keyword:
        tkn.add_rule_assign("package", m_subst, subst_t::expect_package_name);
        tkn.exec_rules();
        break;

    case subst_t::expect_package_name:
        tkn.read_fqn(s_package_name_expected_msg);
        break;
    }
}

void state::package_t::handle_eof()
{
    switch ( m_subst ) {
    case subst_t::expect_package_keyword:
        /* FIDL file is empty. This is okay. */
        return;
    case subst_t::expect_package_name:
        raise_unexpected_eof(s_package_name_expected_msg);
        break;
    }
}
