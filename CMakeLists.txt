# SPDX-FileCopyrightText: 2026 AlloSphere Research Group <allosphere@ucsb.edu>
# SPDX-License-Identifier: BSD-3-Clause
cmake_minimum_required(VERSION 3.11)

project(
  arg_workshop
  DESCRIPTION "ARG code workshop"
  LANGUAGES CXX
  VERSION 0.0.1
)

# cmake scripts are kept in the cmake directory
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# disable in-source builds
include(NoInSourceBuilds)

# enable interprocedural optimization if possible
include(SetIPO)

# set compiler/platform specific flags
# use with caution, preferably only at top level
if(MSVC)
  set(CMAKE_BUILD_PARALLEL_LEVEL $ENV{NUMBER_OF_PROCESSORS})
  # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /STACK:4194304")
endif()

# add source files to executable
add_executable(00_vaomesh)
target_sources(00_vaomesh PRIVATE src/00_vaomesh.cpp)

add_executable(01_shader_quad)
target_sources(01_shader_quad PRIVATE src/01_shader_quad.cpp)

add_executable(02_shader_mesh)
target_sources(02_shader_mesh PRIVATE src/02_shader_mesh.cpp)

add_executable(03_shader_texture)
target_sources(03_shader_texture PRIVATE src/03_shader_texture.cpp)

add_executable(04_instance)
target_sources(04_instance PRIVATE src/04_instance.cpp)

add_executable(05_code_structure)
target_sources(
  05_code_structure
  PRIVATE src/05_code_structure.cpp src/05_moreSrc.cpp
  PRIVATE
    FILE_SET HEADERS
      BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
      BASE_DIRS ${CMAKE_CURRENT_BINARY_DIR}/include
      FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/arg_workshop/05_moreSrc.hpp
)
target_include_directories(
  05_code_structure
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(06_distributed)
target_sources(06_distributed PRIVATE src/06_distributed.cpp)

add_executable(07_shader_distributed)
target_sources(07_shader_distributed PRIVATE src/07_shader_distributed.cpp)

add_executable(08_eqr)
target_sources(
  08_eqr
  PRIVATE src/08_eqr.cpp src/08_renderer.cpp
  PRIVATE
    FILE_SET HEADERS
      BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
      BASE_DIRS ${CMAKE_CURRENT_BINARY_DIR}/include
      FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/arg_workshop/08_renderer.hpp
)
target_include_directories(08_eqr PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(09_lighting)
target_sources(09_lighting PRIVATE src/09_lighting.cpp)

add_executable(10_eqr_ray)
target_sources(10_eqr_ray PRIVATE src/10_eqr_ray.cpp)

# add allolib to project & link
add_subdirectory(allolib EXCLUDE_FROM_ALL)
target_link_libraries(00_vaomesh PRIVATE alapp)
target_link_libraries(01_shader_quad PRIVATE alapp)
target_link_libraries(02_shader_mesh PRIVATE alapp)
target_link_libraries(03_shader_texture PRIVATE alapp)
target_link_libraries(04_instance PRIVATE alapp)
target_link_libraries(05_code_structure PRIVATE alapp)
target_link_libraries(06_distributed PRIVATE alapp)
target_link_libraries(07_shader_distributed PRIVATE alapp)
target_link_libraries(08_eqr PRIVATE alapp)
target_link_libraries(09_lighting PRIVATE alapp)
target_link_libraries(10_eqr_ray PRIVATE alapp)

# add al_ext to project & link
# if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/al_ext)
# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/al_ext)
# get_target_property(AL_EXT_LIBRARIES al_ext AL_EXT_LIBRARIES)
# target_link_libraries(${TARGET_NAME_HERE} PRIVATE ${AL_EXT_LIBRARIES})
# endif()

# example of submodule library usage
# add_subdirectory(external/multi350)
# target_link_libraries(${TARGET_NAME_HERE} PUBLIC multi350)

# example of find_package usage
# find_package(OpenImageIO REQUIRED)
# if(MSVC)
#   target_compile_options(${TARGET_NAME_HERE} PUBLIC /utf-8)
# endif()
# target_link_libraries(${TARGET_NAME_HERE} PUBLIC OpenImageIO::OpenImageIO)

# binaries are put into the ./bin directory by default
set_target_properties(
  00_vaomesh
  01_shader_quad
  02_shader_mesh
  03_shader_texture
  04_instance
  05_code_structure
  06_distributed
  07_shader_distributed
  08_eqr
  09_lighting
  10_eqr_ray
  PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin
)

install(
  TARGETS
    00_vaomesh
    01_shader_quad
    02_shader_mesh
    03_shader_texture
    04_instance
    05_code_structure
    06_distributed
    07_shader_distributed
    08_eqr
    09_lighting
    10_eqr_ray
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION .
  INCLUDES DESTINATION include
)
