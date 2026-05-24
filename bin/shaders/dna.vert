// SPDX-FileCopyrightText: 2025 AlloSphere Research Group <allosphere@ucsb.edu>
// SPDX-License-Identifier: BSD-3-Clause
#version 330

uniform mat4 u_modelMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projMatrix;

layout(location = 0) in vec3 a_position;
layout(location = 2) in vec2 a_texCoord;
layout(location = 4) in vec3 a_offset;

out vec2 v_texCoord;
out float v_rotate;

void main() {
  vec4 pos = u_modelMatrix * vec4(a_position + a_offset, 1.0);
  gl_Position = u_projMatrix * u_viewMatrix * pos;
  v_texCoord = a_texCoord;
  // ID of the instance
  v_rotate = float(gl_InstanceID) * 0.1;
}