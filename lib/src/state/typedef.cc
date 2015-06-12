/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "typedef.hh"

// local includes:
#include "tokeniser.hh"
#include "log.hh"

using namespace franca;

void state::typedef_t::handle_token()
{
    tokeniser_t tkn(m_input);

    switch ( m_subst ) {
    case subst_t::expect_new_typename:
        //m_new_typename = tkn.read_name("A type name is expected.");
        m_subst = subst_t::expect_is_keyword;
        break;

    case subst_t::expect_is_keyword:
        tkn.expect_token("is");
        m_subst = subst_t::expect_existing_typename;
        break;

    case subst_t::expect_existing_typename:
        raise_not_implemented();
        break;
    }
}

void state::typedef_t::handle_eof()
{
    raise_unexpected_eof("A typedef definition is expected.");
}
