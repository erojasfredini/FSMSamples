cmake_minimum_required(VERSION 3.15.0)

# Librerias a linkear e includes
set(INCLUDES)
set(LIBRARIES)
set(LIBRARY_DIRS)

# Headers
set(INCLUDES ${INCLUDES} .)
#get_target_property(SFML_INCLUDE sfml-graphics INTERFACE_INCLUDE_DIRECTORIES)
set(INCLUDES ${INCLUDES} "${SFML_INCLUDE}")
set(INCLUDES ${INCLUDES} "${Box2D_INCLUDE}")
set(INCLUDES ${INCLUDES} "../Libreria/Headers")

# Libraries
set(LIBRARIES ${LIBRARIES} ${SFML_LIBS})
set(LIBRARIES ${LIBRARIES} Box2D)
set(LIBRARIES ${LIBRARIES} glu32)
set(LIBRARIES ${LIBRARIES} "StatePattern")

# Libraries Dirs
set(LIBRARY_DIRS ${LIBRARY_DIRS} "../Libreria/Bin/$<CONFIG>/")
set(LIBRARY_DIRS ${LIBRARY_DIRS} "${SFML_LIB}" "${Box2D_LIB}")

include_directories(${INCLUDES})
link_directories(${LIBRARY_DIRS})

add_compile_definitions(SFML_STATIC)

# Proyecto de ejecutable a generar con codigos
file(GLOB_RECURSE Comportamientos_SOURCES RELATIVE ${PROJECT_SOURCE_DIR}/Src/ *.cpp *.h *.hpp)
add_executable(Comportamientos ${Comportamientos_SOURCES})
target_link_libraries(Comportamientos ${LIBRARIES})

# Capetas de salida
set_target_properties(Comportamientos PROPERTIES PDB_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/Bin/$<CONFIG>")
set_target_properties(Comportamientos PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/Bin/$<CONFIG>")