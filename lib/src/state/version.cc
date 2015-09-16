/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "version.hh"

// local includes:
#include "ast.hh"
#include "ast_node_impl.hh"
#include "entity_impl.hh"
#include "log.hh"
#include "parse_error.hh"
#include "tokeniser.hh"

using namespace franca;

void state::version_t::handle_token()
{
    tokeniser_t tkn(m_input);

    switch ( m_subst ) {
    case subst_t::expect_version_keyword:
        tkn.expect_token("version");
        m_subst = subst_t::expect_open_brace;
        break;

    case subst_t::expect_open_brace:
        tkn.expect_token("{");
        m_subst = subst_t::expect_major_keyword;
        break;

    case subst_t::expect_major_keyword:
        tkn.expect_token("major");
        m_subst = subst_t::expect_major_number;
        break;

    case subst_t::expect_major_number:
        m_major = tkn.read_u32("A major version number is expected.");
        m_subst = subst_t::expect_minor_keyword;
        break;

    case subst_t::expect_minor_keyword:
        tkn.expect_token("minor");
        m_subst = subst_t::expect_minor_number;
        break;

    case subst_t::expect_minor_number:
        m_minor = tkn.read_u32("A minor version number is expected.");
        m_subst = subst_t::expect_close_brace;
        break;

    case subst_t::expect_close_brace:
        tkn.expect_token("}");
        debug() << "Version: major:" << m_major << log_enable_nospace_t() <<
                   "; minor: " << m_minor;
        ast().top_node()->entity()->apply_version(m_major, m_minor);
        leave_state();
        break;
    }
}

void state::version_t::handle_eof()
{
    switch ( m_subst ) {
    case subst_t::expect_version_keyword:
        break;
    case subst_t::expect_open_brace:
    case subst_t::expect_major_keyword:
    case subst_t::expect_major_number:
    case subst_t::expect_minor_keyword:
    case subst_t::expect_minor_number:
    case subst_t::expect_close_brace:
        raise_unexpected_eof("A version specification is expected.");
        break;
    }
}
