/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "franca/entity/typedef.hh"

// local includes:
#include "entity/typedef_impl.hh"

DEFINE_FRANCA_ENTITY(typedef_t, typedef_impl_t, type_t)

using namespace franca::entity;

type_t typedef_t::base_type() const noexcept
{
    return impl()->base_type()->interface();
}
