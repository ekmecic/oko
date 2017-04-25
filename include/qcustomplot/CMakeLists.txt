cmake_minimum_required(VERSION 3.6)
project(qcustomplot)

set(QCUSTOMPLOT_SRC
  qcustomplot.h
  qcustomplot.cpp)

add_library(qcustomplot ${QCUSTOMPLOT_SRC})

find_package(Qt5Core REQUIRED)
target_link_libraries(qcustomplot Qt5::Core)

target_include_directories(qcustomplot PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
