/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "types_or_iface.hh"

// local includes:
#include "tokeniser.hh"
#include "state/type_collection.hh"
#include "state/interface.hh"

using namespace franca;

void state::types_or_iface_t::handle_token()
{
    tokeniser_t tkn(m_input);
    tkn.add_rule("typeCollection", [this]{ enter_substate<state::type_collection_t>(); } );
    tkn.add_rule("interface", [this]{ enter_substate<state::interface_t>(); } );
    tkn.exec_rules();
}
