cmake_minimum_required(VERSION 3.6)
project(easylogging++)

add_library(easylogging++ easylogging++.h)

target_include_directories(easylogging++ PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
