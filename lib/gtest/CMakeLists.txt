###############################################################################
 #                                                                            #
 # This file is a part of GeNa project / Franca IDL.                          #
 #                                                                            #
 ###############################################################################

find_package(GTest REQUIRED)

add_executable(gtest_franca
    tst_common.cc
    tst_types.cc
    tst_fqn_utils.cc
    tst_iface.cc
)

target_include_directories(gtest_franca PRIVATE ${GTEST_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/lib/src)
target_link_libraries(gtest_franca franca ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY})

add_test(gtest_franca gtest_franca)
