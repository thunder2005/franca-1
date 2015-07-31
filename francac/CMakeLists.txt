###############################################################################
 #                                                                            #
 # This file is a part of GeNa project / Franca IDL.                          #
 #                                                                            #
 ###############################################################################

set(SOURCES
    src/main.cc
    src/config.cc
)

add_executable(francac
    ${SOURCES}
    ${HEADERS}
)

target_link_libraries(francac franca)
