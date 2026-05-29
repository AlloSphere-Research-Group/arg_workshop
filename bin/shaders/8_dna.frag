// SPDX-FileCopyrightText: 2025 AlloSphere Research Group <allosphere@ucsb.edu>
// SPDX-License-Identifier: BSD-3-Clause
#version 330

uniform sampler2D u_imageTex;

in vec2 v_texCoord;
in float v_rotate;

layout(location = 0) out vec4 frag_out0;

void main() {
  vec2 rotatedTexCoord = v_texCoord;
  rotatedTexCoord.x = fract(rotatedTexCoord.x + v_rotate);
  vec4 texColor = texture(u_imageTex, rotatedTexCoord);
  frag_out0 = texColor;
}