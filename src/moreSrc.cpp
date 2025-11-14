// SPDX-FileCopyrightText: 2025 AlloSphere Research Group <allosphere@ucsb.edu>
// SPDX-License-Identifier: BSD-3-Clause
#include "moreSrc.hpp"

#include <iostream>

#include "al/graphics/al_Graphics.hpp"

using namespace al;
using namespace exampleNamespace;

void Renderer::init()
{
  mesh.primitive(Mesh::TRIANGLE_STRIP);
  mesh.vertex(-1.f, -1.f, 0);
  mesh.vertex(1.f, -1.f, 0);
  mesh.vertex(-1.f, 1.f, 0);
  mesh.vertex(1.f, 1.f, 0);
  mesh.texCoord(0, 0);
  mesh.texCoord(1, 0);
  mesh.texCoord(0, 1);
  mesh.texCoord(1, 1);
  mesh.color(1, 0, 0);
  mesh.color(1, 1, 0);
  mesh.color(0, 0, 1);
  mesh.color(0, 1, 1);
  mesh.update();
}

void Renderer::isValid()
{
  std::cout << "extra src properly loaded" << std::endl;
}

void Renderer::update(double dt)
{
  phase += dt / period;
  if (phase >= 1.) phase -= 1.;
}

void Renderer::draw(Graphics& g)
{
  g.clear();

  g.pushMatrix();
  g.rotate(phase * 360, 0, 1, 0);
  g.meshColor();  // mesh color
  g.draw(mesh);
  g.popMatrix();
}