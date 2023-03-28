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

add_executable(ocvs main.cpp)



set_target_properties(ocvs
    PROPERTIES CXX_STANDARD 20
)