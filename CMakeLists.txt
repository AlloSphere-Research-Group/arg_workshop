# SPDX-FileCopyrightText: 2026 AlloSphere Research Group <allosphere@ucsb.edu>
# SPDX-License-Identifier: BSD-3-Clause
cmake_minimum_required(VERSION 3.11)

project(arg_workshop
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
add_executable(arg_workshop)
target_sources(arg_workshop PRIVATE
  # src/0_vaomesh.cpp
  # src/1_shader_quad.cpp
  # src/2_shader_mesh.cpp
  # src/3_shader_texture.cpp
  # src/4_instance.cpp
  # src/5_code_structure.cpp
  # src/5_moreSrc.cpp
  src/6_sphere.cpp
)

target_include_directories(arg_workshop PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# add allolib to project & link
add_subdirectory(allolib)
target_link_libraries(arg_workshop PRIVATE alapp)

# add al_ext to project & link
# if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/al_ext)
# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/al_ext)
# get_target_property(AL_EXT_LIBRARIES al_ext AL_EXT_LIBRARIES)
# target_link_libraries(arg_workshop PRIVATE ${AL_EXT_LIBRARIES})
# endif()

# example of submodule library usage
# add_subdirectory(external/multi350)
# target_link_libraries(arg_workshop PUBLIC multi350)

# example of find_package usage
# find_package(OpenImageIO REQUIRED)
# if(MSVC)
#   target_compile_options(arg_workshop PUBLIC /utf-8)
# endif()
# target_link_libraries(arg_workshop PUBLIC OpenImageIO::OpenImageIO)


# binaries are put into the ./bin directory by default
set_target_properties(arg_workshop PROPERTIES
  CXX_STANDARD 20
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
  RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin
  RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin
)