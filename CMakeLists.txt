# *********************************************
# Copylight @Woon2
# simple script for building opencv project
# *********************************************

cmake_minimum_required(VERSION 3.18)

if(NOT DEFINED CMAKE_BUILD_TYPE AND NOT DEFINED CMAKE_CONFIGURATION_TYPES)
    message(STATUS "setting CMAKE_BUILD_TYPE to Release(default)
    as none was specified.")
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE
        PROPERTY STRINGS "Debug" "Release")
endif()

if(NOT DEFINED CMAKE_INSTALL_PREFIX)
    message(STATUS "setting CMAKE_INSTALL_PREFIX to
        ${CMAKE_CURRENT_SOURCE_DIR}/install(default) as none was specified.")
    set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/install")
endif()

project(opencv_study VERSION 2023.03.28 LANGUAGES CXX)

message(STATUS "configuring opencv_study(version ${CMAKE_PROJECT_VERSION})...")
message(STATUS "Author: @Woon2 (wkdauddns9@gmail.com)")

# Find and setup OpenCV
if(NOT DEFINED OpenCV_DIR
    AND NOT DEFINED ENV{OpenCV_DIR})
    message(STATUS "the variable \"OpenCV_DIR\"(a directory which is
        the parent directory of include directory, library directory,
        binary directory, etc.) has not been defined.")

    message(STATUS "searching OpenCV directory in PATH...")
    find_path(OpenCV_DIR 
        NAMES "OpenCVConfig.cmake" "OpenCVConfig-version.cmake"
        PATHS $ENV{Path})

    if (OpenCV_DIR STREQUAL OpenCV_DIR-NOTFOUND)
        message(FATAL_ERROR "OpenCV not found.")
    endif()
endif()

find_package(OpenCV REQUIRED)

# Find and setup google test
if(NOT DEFINED GTEST_ROOT
    AND NOT DEFINED ENV{GTEST_ROOT})
    message(STATUS "the variable \"GTEST_ROOT\" has not been defined.")

    set(GTEST_GIT_URL "https://github.com/google/googletest.git" CACHE STRING
        "github url for google test" FORCE)
    set(GTEST_COMMIT_HASH "d25e625364a2078c940da2cb1fcf098aa184fd9f" CACHE STRING
        "git commit hash for specific google test version" FORCE)

    message(STATUS "downloading google test [${GTEST_COMMIT_HASH}] from ${GTEST_GIT_URL}...")

    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/d25e625364a2078c940da2cb1fcf098aa184fd9f.zip
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    FetchContent_MakeAvailable(googletest)
else()
    find_package(GTest REQUIRED)
endif()

enable_testing()

# Copy dlls to build directory for Windows
if (WIN32)
    find_path(OpenCV_BINDIR
        NAMES "opencv_version.exe" "opencv_versiond.exe"
            "opencv_version_win32.exe" "opencv_version_win32d.exe"
        # it has a possiblity that OpenCV_DIR has not be defined, still okay? 
        PATHS $ENV{Path} $ENV{OpenCV_DIR} ${OpenCV_DIR}
    )

    if(OpenCV_BINDIR STREQUAL OpenCV_BINDIR-NOTFOUND)
        message(FATAL_ERROR "OpenCV binary directory is not found.
            make OpenCV binary directory child of OpenCV_DIR or
            add OpenCV binary directory to PATH.")
    endif()

    file(GLOB OpenCV_BINARY
        "${OpenCV_BINDIR}/*.dll"
        "${OpenCV_BINDIR}/*.pdb")

    file(COPY ${OpenCV_BINARY} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    install(FILES ${OpenCV_BINARY} DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
endif()

# Configure main project

add_executable(ocvs main.cpp mat.hpp experimentLogger.hpp)
add_executable(mat_test matTest.cpp matComparison.hpp)

function(COMMON_CONFIGURATION targetName)
    # See below link for finding GCC options.
    # https://gcc.gnu.org/onlinedocs/gcc/Option-Summary.html
    if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
        target_compile_options(${targetName}
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
            target_compile_options(${targetName}
            PRIVATE
                "/clang:-fcoroutines-ts"
                -fms-compatiability
            )
        else()  # AppleClang or Clang on Linux
            target_compile_options(${targetName}
            PRIVATE
                -std=c++2a
            )
        endif()

    # See below link for finding msvc options.
    # https://docs.microsoft.com/en-us/cpp/build/reference/compiler-options-listed-by-category?view=msvc-160
    elseif(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
        target_compile_options(${targetName}
        PRIVATE
            /Wall
            /JMC-
            /wd4668
            /wd4464
            /wd4514
            /wd5045
            /wd4710
            /wd4711
            /wd4820
            /Zc:__cplusplus
            /Zc:preprocessor
        )
    endif()

    # Platform setting
    # Windows setting already exists, others not yet.
    if(WIN32)
        target_compile_definitions(${targetName}
        PRIVATE
            WIN32_LEAN_AND_MIN NOMINMAX
        )
        set_target_properties(${targetName}
            PROPERTIES
                WINDOWS_EXPORT_ALL_SYMBOLS OFF
        )
    endif()

    set_target_properties(${targetName}
        PROPERTIES CXX_STANDARD 20
    )
endfunction()

COMMON_CONFIGURATION(ocvs)
COMMON_CONFIGURATION(mat_test)

# Link
message(STATUS "OpenCV_DIR is ${OpenCV_DIR}")
target_link_libraries(ocvs ${OpenCV_LIBS})
target_link_libraries(mat_test GTest::gtest_main ${OpenCV_LIBS})

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
        # note: do not wrap the COMMAND with ""
        COMMAND ${GIT_EXECUTABLE} log --pretty=reference -6
    )
endif()

# testing
include(GoogleTest)
gtest_discover_tests(mat_test)