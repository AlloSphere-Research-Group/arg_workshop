// SPDX-FileCopyrightText: 2026 AlloSphere Research Group <allosphere@ucsb.edu>
// SPDX-License-Identifier: BSD-3-Clause
#version 400

uniform float u_osc;
uniform vec3 u_pos;
uniform vec4 u_quat;

in vec2 v_texCoord;

layout(location = 0) out vec4 frag_out0;

const float PI = 3.14159265359;

vec3 rotateVector(vec4 q, vec3 v) {
  return v + 2.0 * cross(q.xyz, cross(q.xyz, v) + q.w * v);
}

bool intersectSphere(vec3 ro, vec3 rd, vec3 center, float radius, out float tHit) {
  vec3 oc = ro - center;
  float b = dot(oc, rd);
  float c = dot(oc, oc) - radius * radius;
  float h = b * b - c;
  if(h < 0.0) {
    return false;
  }

  float s = sqrt(h);
  float tNear = -b - s;
  float tFar = -b + s;
  tHit = (tNear > 0.0) ? tNear : tFar;
  return tHit > 0.0;
}

vec3 gammaCorrect(vec3 linearColor) {
  return pow(max(linearColor, vec3(0.0)), vec3(1.0 / 2.2));
}

void main() {
  float phi = -v_texCoord.x * 2.0 * PI;
  float theta = (v_texCoord.y - 0.5) * PI;

  vec3 rayDir;
  rayDir.x = cos(theta) * sin(phi);
  rayDir.y = sin(theta);
  rayDir.z = cos(theta) * cos(phi);

  rayDir = rotateVector(u_quat, rayDir);
  rayDir = normalize(rayDir);

  vec3 rayOrigin = u_pos;

  vec3 sphereCenter = vec3(0.0, 0.0, -2.0);

  float t;
  if(intersectSphere(rayOrigin, rayDir, sphereCenter, 1.0, t)) {
    vec3 p = rayOrigin + t * rayDir;

    vec3 normal = normalize(p - sphereCenter);
    vec3 viewDir = normalize(rayOrigin - p);

    float lightAngle = (u_osc * 0.5 + 0.5) * 2.0 * PI;
    vec3 lightPos = sphereCenter + vec3(2.0 * cos(lightAngle), 1.0 + 0.5 * sin(lightAngle * 0.7), 2.0 * sin(lightAngle));
    vec3 lightDir = normalize(lightPos - p);
    float ndotv = max(dot(normal, viewDir), 0.0);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 halfDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfDir), 0.0), 64.0);

    // Schlick Fresnel term for a soft rim highlight at grazing angles.
    vec3 f0 = vec3(0.04);
    vec3 fresnel = f0 + (vec3(1.0) - f0) * pow(1.0 - ndotv, 5.0);

    vec3 albedo = vec3(0.95, 0.75, 0.15);
    vec3 ambient = 0.08 * albedo;
    vec3 diffuse = diff * albedo;
    vec3 specular = spec * vec3(1.0);
    vec3 rim = 0.35 * fresnel;
    vec3 lit = ambient + diffuse + specular + rim;

    frag_out0 = vec4(gammaCorrect(lit), 1.0);
    return;
  }

  vec3 bg = vec3(0.1, 0.2, 0.2);
  frag_out0 = vec4(gammaCorrect(bg), 1.0);
}