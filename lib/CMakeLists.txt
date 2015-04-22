###############################################################################
 #                                                                            #
 # This file is a part of GeNa project / Franca IDL.                          #
 #                                                                            #
 ###############################################################################

set(SOURCES
    src/parser.cc
    src/parser_impl.cc
)

set(HEADERS
    src/parser_impl.hh
    src/log.hh
)

set(PUBLIC_HEADERS
    include/franca/parser.hh
    include/franca/logger.hh
)

add_library(franca SHARED
    ${SOURCES}
    ${HEADERS}
    ${PUBLIC_HEADERS}
)

target_include_directories(franca PRIVATE src PUBLIC include)
