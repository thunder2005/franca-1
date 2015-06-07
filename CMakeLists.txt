###############################################################################
 #                                                                            #
 # This file is a part of GeNa project / Franca IDL.                          #
 #                                                                            #
 ###############################################################################

cmake_minimum_required(VERSION 2.8.11)
project("franca")

add_compile_options(-std=c++1y)
add_compile_options(-g)
add_compile_options(-Wall -Wextra -Werror -Wconversion -Wnon-virtual-dtor
                    -Wold-style-cast -pedantic)
add_compile_options(-fno-omit-frame-pointer -fstrict-aliasing)

enable_testing()
add_subdirectory(francac)
add_subdirectory(lib)
