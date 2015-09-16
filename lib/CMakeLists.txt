###############################################################################
 #                                                                            #
 # This file is a part of GeNa project / Franca IDL.                          #
 #                                                                            #
 ###############################################################################

add_subdirectory(gtest)

set(SOURCES
    src/inout.hh
    src/input_context.hh
    src/input_cursor.hh
    src/loggable.cc
    src/loggable_impl.hh
    src/log.hh
    src/parse_error.cc
    src/parser.cc
    src/parser_impl.cc
    src/translation_unit.cc

    # stm:
    src/stm.cc
    src/state.cc
    src/tokeniser.cc
    src/state/package.cc
    src/state/types_or_iface.cc
    src/state/type_collection.cc
    src/state/version.cc
    src/state/typedef.cc
    src/state/interface.cc
    src/state/method.cc
    src/state/argument.cc

    # ast:
    src/ast.cc
    src/ast_flags.hh
    src/ast_node.cc
    src/ast_node_impl.cc
    src/named_entity.hh

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
    src/entity/method.cc
    src/entity/method_impl.cc

    # algo:
    src/algo/test_if_all.hh
)

set(PUBLIC_HEADERS
    include/franca/ast_node.hh
    include/franca/ast_visitor.hh
    include/franca/entity/attr/integer_size.hh
    include/franca/entity/attr/named_type.hh
    include/franca/entity/attr/version.hh
    include/franca/entity.hh
    include/franca/entity/integer.hh
    include/franca/entity/method.hh
    include/franca/entity/package.hh
    include/franca/entity/type_collection.hh
    include/franca/entity/typedef.hh
    include/franca/entity/type.hh
    include/franca/input_factory.hh
    include/franca/input_provider.hh
    include/franca/logger.hh
    include/franca/parser.hh
)

add_library(franca SHARED
    ${SOURCES}
    ${PUBLIC_HEADERS}
)

target_include_directories(franca PRIVATE src PUBLIC include)
