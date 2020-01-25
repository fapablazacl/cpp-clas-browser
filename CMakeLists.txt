cmake_minimum_required(VERSION 3.16)

project(cpp-class-browser)

find_package(PkgConfig)
pkg_check_modules (GTKMM gtkmm-3.0 gtksourceviewmm-3.0 gdlmm-3.0)

link_directories (${GTKMM_LIBRARY_DIRS})
include_directories (${GTKMM_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set (target cpp-class-browser)

add_executable(${target} main.cpp)
target_link_libraries(${target} ${GTKMM_LIBRARIES})
