/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

namespace franca {

class ast_node_t;

namespace entity {
class integer_t;
class package_t;
class type_collection_t;
class typedef_t;
}

class ast_visitor_t
{
public:
    //! Virtual destructor.
    virtual ~ast_visitor_t() = default;

public:
    virtual void visit( const ast_node_t & /* node */ ) {}
    virtual void visit( const entity::package_t & /* package */ ) {}
    virtual void visit( const entity::type_collection_t & /* tc */ ) {}
    virtual void visit( const entity::integer_t & /* type */ ) {}
    virtual void visit( const entity::typedef_t & /* type */ ) {}
};

} // namespace franca
