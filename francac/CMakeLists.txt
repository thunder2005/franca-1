###############################################################################
 #                                                                            #
 # This file is a part of GeNa project / Franca IDL.                          #
 #                                                                            #
 ###############################################################################

set(SOURCES
    src/main.cc
    src/config.cc
    src/input_provider.cc
    src/input_factory.cc
)

add_executable(francac
    ${SOURCES}
    ${HEADERS}
)

target_link_libraries(francac franca)
