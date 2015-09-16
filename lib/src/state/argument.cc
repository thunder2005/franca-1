/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "argument.hh"

// local includes:
#include "ast.hh"
#include "ast_node_impl.hh"
#include "entity_impl.hh"
#include "entity/type_impl.hh"
#include "log.hh"
#include "named_entity.hh"
#include "parse_error.hh"
#include "tokeniser.hh"

using namespace franca;

void state::argument_t::handle_token()
{
    tokeniser_t tkn(m_input);

    switch ( m_subst ) {
    case subst_t::expect_typename:
        m_given_typename = tkn.read_fqn("A type of an argument is expected.");
        m_type = ast().existing_type(m_given_typename);
        m_subst = subst_t::expect_argument_name;
        break;

    case subst_t::expect_argument_name:
        finalise_argument(
                    tkn.read_typename("A name of an argument is expected."));
        leave_state();
        break;
    }
}

void state::argument_t::finalise_argument( const std::string &name )
{
    debug() << "Argument:" << name << "of type" << m_given_typename;
    ast().top_entity()->apply_argument({name, m_type});
}

void state::argument_t::handle_eof()
{
    raise_unexpected_eof("A valid method argument is expected.");
}
