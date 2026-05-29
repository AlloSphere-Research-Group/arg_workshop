// SPDX-FileCopyrightText: 2025 AlloSphere Research Group <allosphere@ucsb.edu>
// SPDX-License-Identifier: BSD-3-Clause
#version 330

// check out other variants of sampler (2Darray, 3D, cube)
uniform sampler2D u_imageTex;
uniform vec4 u_lightColor;
uniform float u_doorAngle;

in vec3 v_position;
in vec2 v_texCoord;
in vec3 v_normal;

layout(location = 0) out vec4 frag_out0;

void main() {
  // retrieve the texture color from the according position in the image
  vec4 texColor = texture(u_imageTex, v_texCoord);

  // need to send as uniform if door pos changes
  vec3 doorCenter = vec3(5, 0, -11);

  vec3 lightDir = normalize(v_position - doorCenter);
  vec2 lightDirXZ = normalize(lightDir.xz);
  vec2 zAxisXZ = vec2(0.0, -1.0);
  float angleXZ = degrees(acos(clamp(dot(lightDirXZ, zAxisXZ), -1.0, 1.0)));

  vec3 normal = normalize(v_normal);
  // technically should be 0 but adding some to count for light bouncing around the room
  float diff = max(dot(normal, lightDir), 0.2);
  vec4 light = u_lightColor * diff;

  // adding a little bit of bias to correctly compare 0 angle with the step function
  // multiplying 0.5 is just an arbitrary choice to darken the room
  frag_out0 = 0.5 * texColor + step(angleXZ, u_doorAngle - 1e-5) * light;
}