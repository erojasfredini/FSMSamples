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

option(FIND_PACKAGE "Buscar los paquetes o usar los del repo" ON)
if (FIND_PACKAGE)
    # Buscar el paquete
    option(SFML_STATIC_LIBRARIES "Usar biblioteca estática para SFML" ON)

    find_package(SFML COMPONENTS system window graphics main REQUIRED)
    find_package(Box2D REQUIRED)

    set(Box2D_INCLUDE "${Box2D_DIR}/../../../include")
    set(Box2D_LIB "${Box2D_DIR}/../../.")

    get_target_property(SFML_INCLUDE sfml-graphics INTERFACE_INCLUDE_DIRECTORIES)
    set(SFML_LIBS sfml-window sfml-system sfml-main sfml-graphics)
else()
    # Usar la version en el repositorio
    set(SFML_INCLUDE "../Externo/SFML/include/")
    set(SFML_LIB "../Externo/SFML/lib/")
    set(SFML_LIBS "sfml-window-s-d" "sfml-system-s-d" "sfml-main-d" "sfml-graphics-s-d" "OpenGL32" "freetype" "winmm")

    set(Box2D_INCLUDE "../Externo/box2d/include/")
    set(Box2D_LIB "../Externo/box2d/lib/vs2019/$<CONFIG>")
endif()

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