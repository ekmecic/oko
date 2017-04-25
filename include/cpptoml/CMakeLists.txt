cmake_minimum_required(VERSION 3.6)
project(cpptoml)

add_library(cpptoml cpptoml.h)

target_include_directories(cpptoml PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
