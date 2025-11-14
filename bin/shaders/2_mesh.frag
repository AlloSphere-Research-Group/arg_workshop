// SPDX-FileCopyrightText: 2025 AlloSphere Research Group <allosphere@ucsb.edu>
// SPDX-License-Identifier: BSD-3-Clause
#version 330

in vec3 v_pos;

layout(location = 0) out vec4 frag_out0;

void main() {
  vec4 meshColor = vec4(0.5 * (v_pos + 1.), 1.);

  frag_out0 = meshColor;
}