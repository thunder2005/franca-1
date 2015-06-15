/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "typedef.hh"

// local includes:
#include "tokeniser.hh"
#include "ast.hh"

using namespace franca;

void state::typedef_t::handle_token()
{
    tokeniser_t tkn(m_input);

    switch ( m_subst ) {
    case subst_t::expect_new_typename:
        process_new_typename(
                    tkn.read_typename("A typedef name is expected."));
        m_subst = subst_t::expect_is_keyword;
        break;

    case subst_t::expect_is_keyword:
        tkn.expect_token("is");
        m_subst = subst_t::expect_existing_typename;
        break;

    case subst_t::expect_existing_typename:
        process_existing_typename(
                    tkn.read_fqn("An existing type name is expected."));
        leave_state();
        break;
    }
}

void state::typedef_t::handle_eof()
{
    raise_unexpected_eof("A typedef definition is expected.");
}

void state::typedef_t::process_new_typename( const std::string &tname )
{
    auto type = ast().type(tname);
    if ( type /* == exists */ ) {
        raise_type_exists(tname.c_str());
    }
    m_new_typename = tname;
}

void state::typedef_t::process_existing_typename( const std::string &tname )
{
    auto type = ast().type(tname);
    if ( !type /* == not exists */ ) {
        raise_type_not_found(tname.c_str());
    }
    raise_not_implemented("typedef");
}
