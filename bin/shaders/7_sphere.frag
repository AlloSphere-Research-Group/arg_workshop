// SPDX-FileCopyrightText: 2025 AlloSphere Research Group <allosphere@ucsb.edu>
// SPDX-License-Identifier: BSD-3-Clause
#version 330

// check out other variants of sampler (2Darray, 3D, cube)
uniform sampler2D u_imageTex;
uniform vec4 u_color;
uniform float u_mix;

in vec2 v_texCoord;

layout(location = 0) out vec4 frag_out0;

void main() {
  // retrieve the texture color from the according position in the image
  vec4 texColor = texture(u_imageTex, v_texCoord);
  texColor = mix(u_color, texColor, u_mix);
  frag_out0 = texColor;
}