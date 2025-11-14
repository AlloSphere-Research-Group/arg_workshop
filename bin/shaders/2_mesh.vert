// SPDX-FileCopyrightText: 2025 AlloSphere Research Group <allosphere@ucsb.edu>
// SPDX-License-Identifier: BSD-3-Clause
#version 330

uniform mat4 u_modelMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projMatrix;

layout(location = 0) in vec3 a_position;

out vec3 v_pos;

void main() {
  vec4 pos = u_modelMatrix * vec4(a_position, 1.0);
  v_pos = pos.xyz; // after model matrix(translate) has been applied
  // v_pos = a_position; // before
  gl_Position = u_projMatrix * u_viewMatrix * pos;
}