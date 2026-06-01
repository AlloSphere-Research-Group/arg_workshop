// SPDX-FileCopyrightText: 2026 AlloSphere Research Group <allosphere@ucsb.edu>
// SPDX-License-Identifier: BSD-3-Clause
#version 330

uniform mat4 u_modelMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projMatrix;
uniform float u_eyeSep;
uniform float u_focLen;

layout(location = 0) in vec3 a_position;
layout(location = 2) in vec2 a_texCoord;
layout(location = 3) in vec3 a_normal;

out vec3 v_position;
out vec2 v_texCoord;
out vec3 v_normal;

vec4 stereo_displace(vec4 v, float e, float f) {
  // eye to vertex distance
  float l = sqrt((v.x - e) * (v.x - e) + v.y * v.y + v.z * v.z);
  // absolute z-direction distance
  float z = abs(v.z);
  // x coord of projection of vertex on focal plane when looked from eye
  float t = f * (v.x - e) / z;
  // x coord of displaced vertex to make displaced vertex be projected on focal plane
  // when looked from origin at the same point original vertex would be projected
  // when looked form eye
  v.x = z * (e + t) / f;
  // set distance from origin to displaced vertex same as eye to original vertex
  v.xyz = normalize(v.xyz);
  v.xyz *= l;
  return v;
}

void main() {
  vec4 pos = u_modelMatrix * vec4(a_position, 1.0);
  gl_Position = u_projMatrix * stereo_displace(u_viewMatrix * pos, u_eyeSep, u_focLen);
  v_position = pos.xyz;
  v_texCoord = a_texCoord;
  vec4 norm = u_modelMatrix * vec4(a_normal, 1.0);
  v_normal = norm.xyz;
}