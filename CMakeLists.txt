cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

project(oko CXX)
set(TARGET ${CMAKE_PROJECT_NAME})

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5PrintSupport REQUIRED)
find_package(Qt5Bluetooth REQUIRED)
set(QT5_LIBRARIES Qt5::Widgets Qt5::PrintSupport Qt5::Bluetooth)

add_subdirectory(include/cpptoml)
add_subdirectory(include/qcustomplot)
add_subdirectory(include/easylogging++)

file(GLOB OKO_SOURCES
  src/*.cpp
  src/*.h)
set(UI_SOURCES src/mainwindow.ui)
qt5_wrap_ui(UI_GENERATED_HEADERS ${UI_SOURCES})

add_executable(${TARGET} ${OKO_SOURCES} ${UI_GENERATED_HEADERS})

target_link_libraries(${TARGET} ${QT5_LIBRARIES})
target_link_libraries(${TARGET} cpptoml)
target_link_libraries(${TARGET} easylogging++)
target_link_libraries(${TARGET} qcustomplot)
