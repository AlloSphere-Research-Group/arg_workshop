// SPDX-FileCopyrightText: 2026 AlloSphere Research Group <allosphere@ucsb.edu>
// SPDX-License-Identifier: BSD-3-Clause
#version 330

uniform samplerCube pixelMap;

in vec2 tex_coord;

layout(location = 0) out vec4 frag_out0;

void main() {
  const float PI = 3.14159265359;

  float phi = -tex_coord.x * 2.0 * PI;
  float theta = (tex_coord.y - 0.5) * PI;

  vec3 pixelDir;
  pixelDir.x = cos(theta) * sin(phi);
  pixelDir.y = sin(theta);
  pixelDir.z = cos(theta) * cos(phi);

  vec4 texColor = texture(pixelMap, pixelDir);

  frag_out0 = texColor;
}