// SPDX-FileCopyrightText: 2025 AlloSphere Research Group <allosphere@ucsb.edu>
// SPDX-License-Identifier: BSD-3-Clause
#version 330

layout(location = 0) in vec3 a_position;
layout(location = 2) in vec2 a_texCoord; // vaomesh setup

// parameter being passed to geometry/fragment shaders
out vec2 v_texCoord;

void main() {
  v_texCoord = a_texCoord;
  // gl_Position receives homogenous 4D vector
  gl_Position = vec4(a_position, 1);
}