####################################################################################
# Welcome to the CMake build system for StatePattern Steering Behaviours examples. #
# This is the main file where the general build environment is set-up and the      #
# the build configuration options are initialized.                                 #
####################################################################################

cmake_minimum_required(VERSION 3.15.0)

##################################################################
#############               SOLUTION                 #############
##################################################################

project(FSM LANGUAGES CXX)
# Version
set (FSM_VERSION_MAJOR 1)
set (FSM_VERSION_MINOR 0)

##################################################################
#############                CONFIG                  #############
##################################################################

option(SFML_STATIC_LIBRARIES "Usar biblioteca estática para SFML" ON)

find_package(SFML COMPONENTS system window graphics main REQUIRED)

find_package(Box2D REQUIRED)

##################################################################
#############        Comportamientos PROJECT         #############
##################################################################

add_subdirectory(Comportamientos/)

##################################################################
#############             Duelo PROJECT              #############
##################################################################

add_subdirectory(Duelo/)

##################################################################
#############           GENERAL CONFIG               #############
##################################################################

# Make CXX_STANDARD version a requirement (it won't compile with older version)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Visual Studio specific config
if (MSVC)
    # Multiprocesor compilation
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP" CACHE STRING "compile flags" FORCE)
endif ()