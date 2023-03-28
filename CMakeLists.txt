# *********************************************
# Copylight @Woon2
# simple script for building opencv project
# *********************************************

cmake_minimum_required(VERSION 3.18)

project(opencv_study VERSION 2023.03.28 LANGUAGES CXX)

add_executable(ocvs main.cpp)

set_target_properties(ocvs
    PROPERTIES CXX_STANDARD 20
)