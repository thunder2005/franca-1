# franca
A parser and a compiler for Franca IDL.

## language specification
This chapter contains a specification of Franca IDL, as it is supported by this
project. It is based on the official Franca IDL 0.3.0 user guide (it can be found
inside *doc* directory).

### fully qualified names
Everything in Franca IDL (types, interfaces, methods etc.) has an associated unique
fully qualified name (or short: FQN). It is a sequence of identifiers (at least one)
separated by dots. The identifiers may contain only letters of basic Latin alphabet
and digits. The identifiers may not start with a digit.

### franca file
Franca IDL files' extension is ".fidl". These are plain text files encoded in
UTF-8.

An empty file is a valid Franca file.

#### package declaration
Syntax:

    package <package's fqn>

Each non-empty Franca file must start with a package declaration. It consists of
a *package* keyword, followed by an FQN of this package. It puts all type collections
and interfaces defined in this file into the package. The package's FQN will be
prepended to FQNs of all entities defined in the file.

Example:

    package test.franca.idl
    interface SomeInterface {
        // this interface can be globally accessed by the FQN
        // test.franca.idl.SomeInterface
    }

#### type collection definition
Syntax:

    typeCollection <collection's fqn> {
      [ version { major <number> minor <number> } ]
      [ <user defined types> ]
    }

A type collection is a (maybe empty) set of user-defined types. Each type collection's
definition consists of a *typeCollection* keyword, followed by an FQN and a body
block (*{ ... }*) of this type collection.

The body block consists of an optional version number (with major/minor scheme)
and of zero or more type definitions: typedefs, structures, arrays, enumerations,
maps and/or unions.

As type collections are just a plain collection of user-defined types, inheritance
is not supported for them. All user-defined types inside a type collection have
global visibility, i.e. they can be used for defining interfaces as well as
user-defined types in the same or another type collection.

##### predefined types
These predefined types are supported: *Int8*, *UInt8*, *Int16*, *UInt16*, *Int32*,
*UInt32*, *Int64*, *UInt64*, *Boolean*, *Float*, *Double*, *String* and *ByteBuffer*.

##### typedef definition
Syntax:

    typedef <new type's name> is <existing type's name>

Typedefs can be used to create new type names which are simple aliases for
existing types.
