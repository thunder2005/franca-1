###############################################################################
 #                                                                            #
 # This file is a part of GeNa project / Franca IDL.                          #
 #                                                                            #
 ###############################################################################

cmake_minimum_required(VERSION 2.8.11)
project("franca")

add_compile_options(-std=c++11)
add_compile_options(-g)
add_compile_options(-Wall -Wextra -Werror -Wconversion -pedantic)

enable_testing()
add_subdirectory(francac)
