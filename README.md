# franca
A parser and a compiler for Franca IDL.

# language specification
This chapter contains a specification of Franca IDL, as it is supported by this
project. It is based on the official Franca IDL 0.3.0 user guide (it can be found
inside *doc* directory).

## fully qualified names
Everything in Franca IDL (types, interfaces, methods etc.) has an associated unique
fully qualified name (or short: FQN). It is a sequence of identifiers (at least one)
separated by dots. The identifiers may contain only letters of basic Latin alphabet
and digits. The identifiers may not start with a digit.

## franca file
Franca IDL files' extension is ".fidl". These are plain text files encoded in
UTF-8.

An empty file is a valid Franca file.

### package declaration
Syntax:
    package <package's fqn>

Each non-empty Franca file must start with a package declaration. It consists of
a *package* keyword, followed by an FQN of this package.

This puts all type collections and interfaces defined in this file into the package.
The package's FQN will be prepended to FQNs of all entities defined in the file.

Example:
    package test.franca.idl
    interface SomeInterface {
        // this interface can be globally accessed by the FQN
        // test.franca.idl.SomeInterface
    }
