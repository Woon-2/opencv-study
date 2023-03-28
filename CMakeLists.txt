# *********************************************
# Copylight @Woon2
# simple script for building opencv project
# *********************************************

cmake_minimum_required(VERSION 3.18)

if (NOT DEFINED CMAKE_BUILD_TYPE AND NOT DEFINED CMAKE_CONFIGURATION_TYPES)
    message(STATUS "setting CMAKE_BUILD_TYPE to Release(default)
    as none was specified.")
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE
        PROPERTY STRINGS "Debug" "Release")
endif()

if (NOT DEFINED CMAKE_INSTALL_PREFIX)
    message(STATUS "setting CMAKE_INSTALL_PREFIX to
        ${CMAKE_CURRENT_SOURCE_DIR}/install(default) as none was specified.")
    set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/install")
endif()

project(opencv_study VERSION 2023.03.28 LANGUAGES CXX)

message(STATUS "configuring opencv_study(version ${CMAKE_PROJECT_VERSION})...")
message(STATUS "Author: @Woon2 (wkdauddns9@gmail.com)")

add_executable(ocvs main.cpp)

# See below link for finding GCC options.
# https://gcc.gnu.org/onlinedocs/gcc/Option-Summary.html
if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    target_compile_options(ocvs
    PRIVATE
        -fconcepts
        -Wall
        -pedantic
        -Wextra
    )

# See below link for finding Clang options.
# https://clang.llvm.org/docs/ClangCommandLineReference.html
elseif(CMAKE_CXX_COMPILER_ID MATCHES CLANG)
    # Clang options differ by platform.
    if(WIN32)  # clang-cl
        target_compile_options(ocvs
        PRIVATE
            "/clang:-fcoroutines-ts"
            -fms-compatiability
        )
    else()  # AppleClang or Clang on Linux
        target_compile_options(ocvs
        PRIVATE
            -std=c++2a
        )
    endif()

# See below link for finding msvc options.
# https://docs.microsoft.com/en-us/cpp/build/reference/compiler-options-listed-by-category?view=msvc-160
elseif(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
    target_compile_options(ocvs
    PRIVATE
        /Wall
        /JMC-
        /wd4668
        /wd4464
        /wd4514
        /wd5045
        /Zc:__cplusplus
        /Zc:preprocessor)
endif()

# Platform setting
# Windows setting already exists, others not yet.
if(WIN32)
    target_compile_definitions(ocvs
    PRIVATE
        WIN32_LEAN_AND_MIN NOMINMAX
    )
    set_target_properties(ocvs
        PROPERTIES
            WINDOWS_EXPORT_ALL_SYMBOLS OFF
    )
endif()

set_target_properties(ocvs
    PROPERTIES CXX_STANDARD 20
)

# Installation
install(TARGETS ocvs
    RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin"
    LIBRARY DESTINATION "${CMAKE_INSTALL_PREFIX}/lib"
    ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/arc"
    INCLUDES DESTINATION "${CMAKE_INSTALL_PREFIX}/inc"
)

# Git log custom target
find_package(Git)
if(GIT_FOUND)
    add_custom_target(gitlog
        COMMENT "Git Commit Log:"
        COMMAND "${GIT_EXECUTABLE} --pretty=reference -6"
    )
endif()