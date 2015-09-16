/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

// self-include:
#include "method_impl.hh"

// franca includes:
#include <franca/entity/method.hh>
#include <franca/ast_visitor.hh>

// local includes:
#include "parse_error.hh"
#include "algo/test_if_all.hh"

// std includes:
#include <cassert>

DEFINE_FRANCA_ENTITY_IMPL(method_t, method_impl_t)

using namespace franca::entity;

std::shared_ptr<method_impl_t> method_impl_t::create()
{
    return std::make_shared<method_impl_t>(private_ctr{});
}

method_impl_t::method_impl_t( private_ctr )
{
}

void method_impl_t::apply_argument( const named_entity_t &arg )
{
    /* The given argument name should not be already used for any in or
     * out arguments. */

    const auto &name = arg.name();
    auto same_name_test = [&name]( const named_entity_t &other ) {
        return other.name() == name;
    };

    if ( algo::test_if_all(same_name_test, m_in_args, m_out_args) ) {
        raise_arg_name_already_used(name.c_str());
    }

    /* Save the argument. */

    switch ( m_direction ) {
    case inout_t::in:
        m_in_args.push_back(arg);
        break;

    case inout_t::out:
        m_out_args.push_back(arg);
        break;

    default:
        /* A client code should specify the direction before adding arguments. */
        assert(false);
    }
}
