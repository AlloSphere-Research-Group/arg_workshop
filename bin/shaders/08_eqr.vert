// SPDX-FileCopyrightText: 2026 AlloSphere Research Group <allosphere@ucsb.edu>
// SPDX-License-Identifier: BSD-3-Clause
#version 330

layout(location = 0) in vec3 position;
layout(location = 2) in vec2 texCoord;

out vec2 tex_coord;

void main() {
  tex_coord = texCoord;
  gl_Position = vec4(position, 1);
}