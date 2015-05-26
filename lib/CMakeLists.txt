###############################################################################
 #                                                                            #
 # This file is a part of GeNa project / Franca IDL.                          #
 #                                                                            #
 ###############################################################################

add_subdirectory(gtest)

set(SOURCES
    src/parser.cc
    src/parser_impl.cc
    src/stm.cc
    src/state.cc
    src/state/package.cc
)

set(HEADERS
    src/parse_error.hh
    src/log.hh
)

set(PUBLIC_HEADERS
    include/franca/parser.hh
    include/franca/logger.hh
    include/franca/input_provider.hh
)

add_library(franca SHARED
    ${SOURCES}
    ${HEADERS}
    ${PUBLIC_HEADERS}
)

target_include_directories(franca PRIVATE src PUBLIC include)
