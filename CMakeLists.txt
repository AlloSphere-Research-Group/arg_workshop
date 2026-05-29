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
# not recommended these days
if(MSVC)
  set(CMAKE_BUILD_PARALLEL_LEVEL $ENV{NUMBER_OF_PROCESSORS})

  # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /STACK:4194304")
endif()

# add source files to executable
add_executable(0_vaomesh)
target_sources(0_vaomesh PRIVATE src/0_vaomesh.cpp)

add_executable(1_shader_quad)
target_sources(1_shader_quad PRIVATE src/1_shader_quad.cpp)

add_executable(2_shader_mesh)
target_sources(2_shader_mesh PRIVATE src/2_shader_mesh.cpp)

add_executable(3_shader_texture)
target_sources(3_shader_texture PRIVATE src/3_shader_texture.cpp)

add_executable(4_instance)
target_sources(4_instance PRIVATE src/4_instance.cpp)

add_executable(5_code_structure)
target_sources(
  5_code_structure
  PRIVATE src/5_code_structure.cpp src/5_moreSrc.cpp
  PRIVATE
    FILE_SET HEADERS
      BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
      BASE_DIRS ${CMAKE_CURRENT_BINARY_DIR}/include
      FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/arg_workshop/5_moreSrc.hpp
)
target_include_directories(
  5_code_structure
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(6_distributed)
target_sources(6_distributed PRIVATE src/6_distributed.cpp)

add_executable(7_shader_distributed)
target_sources(7_shader_distributed PRIVATE src/7_shader_distributed.cpp)

add_executable(8_eqr)
target_sources(
  8_eqr
  PRIVATE src/8_eqr.cpp src/8_renderer.cpp
  PRIVATE
    FILE_SET HEADERS
      BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
      BASE_DIRS ${CMAKE_CURRENT_BINARY_DIR}/include
      FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/arg_workshop/8_renderer.hpp
)
target_include_directories(8_eqr PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(9_lighting)
target_sources(9_lighting PRIVATE src/9_lighting.cpp)

# add allolib to project & link
add_subdirectory(allolib EXCLUDE_FROM_ALL)
target_link_libraries(0_vaomesh PRIVATE alapp)
target_link_libraries(1_shader_quad PRIVATE alapp)
target_link_libraries(2_shader_mesh PRIVATE alapp)
target_link_libraries(3_shader_texture PRIVATE alapp)
target_link_libraries(4_instance PRIVATE alapp)
target_link_libraries(5_code_structure PRIVATE alapp)
target_link_libraries(6_distributed PRIVATE alapp)
target_link_libraries(7_shader_distributed PRIVATE alapp)
target_link_libraries(8_eqr PRIVATE alapp)
target_link_libraries(9_lighting PRIVATE alapp)
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
  0_vaomesh
  1_shader_quad
  2_shader_mesh
  3_shader_texture
  4_instance
  5_code_structure
  6_distributed
  7_shader_distributed
  8_eqr
  9_lighting
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
    0_vaomesh
    1_shader_quad
    2_shader_mesh
    3_shader_texture
    4_instance
    5_code_structure
    6_distributed
    7_shader_distributed
    8_eqr
    9_lighting
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION .
  INCLUDES DESTINATION include
)
