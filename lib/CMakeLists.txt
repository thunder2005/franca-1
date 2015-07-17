###############################################################################
 #                                                                            #
 # This file is a part of GeNa project / Franca IDL.                          #
 #                                                                            #
 ###############################################################################

add_subdirectory(gtest)

set(SOURCES
    src/parser.cc
    src/parser_impl.cc

    # stm:
    src/stm.cc
    src/state.cc
    src/tokeniser.cc
    src/state/package.cc
    src/state/types_or_iface.cc
    src/state/type_collection.cc
    src/state/version.cc
    src/state/typedef.cc

    # ast:
    src/ast.cc
    src/ast_node.cc
    src/ast_node_impl.cc

    # entities:
    src/entity.cc
    src/entity_impl.cc
    src/entity/package.cc
    src/entity/package_impl.cc
    src/entity/type_collection.cc
    src/entity/type_collection_impl.cc
    src/entity/type.cc
    src/entity/type_impl.cc
    src/entity/integer.cc
    src/entity/integer_impl.cc
    src/entity/typedef.cc
    src/entity/typedef_impl.cc
)

set(HEADERS
    src/parse_error.hh
    src/log.hh
    src/input_line.hh
    src/ast_flags.hh
)

set(PUBLIC_HEADERS
    include/franca/parser.hh
    include/franca/logger.hh
    include/franca/input_provider.hh
    include/franca/ast_node.hh
    include/franca/ast_visitor.hh
    include/franca/entity.hh
    include/franca/entity/version.hh
    include/franca/entity/package.hh
    include/franca/entity/type_collection.hh
    include/franca/entity/type.hh
    include/franca/entity/integer.hh
    include/franca/entity/integer_size.hh
    include/franca/entity/typedef.hh
)

add_library(franca SHARED
    ${SOURCES}
    ${HEADERS}
    ${PUBLIC_HEADERS}
)

target_include_directories(franca PRIVATE src PUBLIC include)
