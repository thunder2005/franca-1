// self-include:
#include "type_impl.hh"

// franca includes:
#include "franca/entity/type.hh"

using namespace franca::entity;

type_t type_impl_t::interface() noexcept
{
    return type_t(shared_from_this());
}
