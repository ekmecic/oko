cmake_minimum_required(VERSION 2.8.11)

project(oko)

#
# Qt5 support
#
# general overview:
#  * [Modern CMake with Qt and Boost](http://www.kdab.com/modern-cmake-with-qt-and-boost/)
#  * [Using CMake with Qt 5](http://www.kdab.com/using-cmake-with-qt-5/)
#
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5PrintSupport REQUIRED)
find_package(Qt5Bluetooth REQUIRED)

set(QT5_LIBRARIES Qt5::Widgets Qt5::PrintSupport Qt5::Bluetooth)

#
# project main
#
set(TARGET ${CMAKE_PROJECT_NAME})

file(GLOB SOURCES
  src/*.cpp
  src/*.h
  lib/*/*.cpp
  lib/*/*.cpp
)

include_directories(lib src)

set(UI_SOURCES
    src/mainwindow.ui
)

# Stop annoying default log file generation behavior
add_definitions(-DELPP_NO_DEFAULT_LOG_FILE)

#
# Generate necessary headers from .ui files. (qmake lets `uic` do this job.)
# hint from [Cross-platform Qt5 project using cmake](http://stackoverflow.com/questions/21174586/cross-platform-qt5-project-using-cmake)
#
qt5_wrap_ui(UI_GENERATED_HEADERS ${UI_SOURCES})

#
# IMPORTANT: Adding generated headers to target as dependencies
# hint from [unable to include a ui_form header of QT5 in cmake](http://stackoverflow.com/questions/16245147/unable-to-include-a-ui-form-header-of-qt5-in-cmake)
#
add_executable(${TARGET} ${SOURCES} ${UI_GENERATED_HEADERS})

#
# `target_link_libraries()` rather than `qt5_use_modules()` for CMake 2.8.11 or later
# hint from [CMake & QT5 - QT5_WRAP_UI not generating ui header files](http://stackoverflow.com/questions/25875255/cmake-qt5-qt5-wrap-ui-not-generating-ui-header-files)
#
target_link_libraries(${TARGET} ${QT5_LIBRARIES})
