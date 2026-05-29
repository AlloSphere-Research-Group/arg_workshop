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

add_executable(9_lighting)
target_sources(9_lighting PRIVATE src/9_lighting.cpp)

# add allolib to project & link
add_subdirectory(allolib)
target_link_libraries(9_lighting PRIVATE alapp)

# binaries are put into the ./bin directory by default
set_target_properties(
  9_lighting
  PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin
)
