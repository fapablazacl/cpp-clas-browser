find_package(LLVM REQUIRED)
find_package(Clang REQUIRED)

find_package(PkgConfig)
pkg_check_modules (GTKMM gtkmm-3.0 gtksourceviewmm-3.0 gdlmm-3.0)

link_directories (
    ${GTKMM_LIBRARY_DIRS}
    ${LLVM_LIBRARY_DIRS}
    ${CLANG_LIBRARY_DIRS}
)

include_directories (
    ${LLVM_INCLUDE_DIRS}
    ${CLANG_INCLUDE_DIRS}
    ${GTKMM_INCLUDE_DIRS}
)

add_definitions(${LLVM_CFLAGS})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set (target cpp-class-browser)
set (sources 
    main.cpp
    MainWindow.hpp
    MainWindow.cpp
)

add_executable(${target} ${sources})

target_link_libraries(${target} 
    ${GTKMM_LIBRARIES}
    ${LLVM_LIBNAMES}
    libclang
)
