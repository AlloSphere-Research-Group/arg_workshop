// SPDX-FileCopyrightText: 2025 AlloSphere Research Group <allosphere@ucsb.edu>
// SPDX-License-Identifier: BSD-3-Clause
#version 330

uniform float u_osc;

in vec2 v_texCoord;

layout(location = 0) out vec4 frag_out0;

void main() {
  vec4 color =  vec4(v_texCoord, 0.5 * (u_osc + 1.), 1.);

  frag_out0 = color;
}