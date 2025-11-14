// SPDX-FileCopyrightText: 2025 AlloSphere Research Group <allosphere@ucsb.edu>
// SPDX-License-Identifier: BSD-3-Clause
#include "al/app/al_App.hpp"
#include "al/graphics/al_Shapes.hpp"
#include "al/graphics/al_VAOMesh.hpp"

using namespace al;

struct MyApp : App {
  Mesh mesh;
  // Mesh class using VAO
  // VAOMesh mesh;
  double phase = 0;

  void onCreate() override
  {
    lens().near(0.1).far(25).fovy(45);
    nav().pos(0, 0, 4);

    // Manually creating a mesh
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

    // Using al_Shapes.hpp to use 'presets'
    // addTetrahedron(mesh);

    // addTexSphere(mesh, 1, 2048);

    // need to push mesh data to VAO if using VAOMesh
    // mesh.update();
  }

  void onAnimate(double dt) override
  {
    double period = 10;
    phase += dt / period;
    if (phase >= 1.) phase -= 1.;
  }

  void onDraw(Graphics& g) override
  {
    g.clear(0, 0, 0);

    // option to change polygon mode (point, line, fill)
    // can use our OpenGL wrapper, or raw OpenGL
    // g.polygonLine();
    // gl::polygonMode(GL_LINE);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    g.pushMatrix();
    g.rotate(phase * 360, 0, 1, 0);

    // option to change coloring method
    // g.color(1);  // static color
    g.meshColor();  // mesh color
    // g.texture(); // texture
    // g.material(); // material

    // using the draw method of the graphics class
    // updating the internal vao
    g.draw(mesh);
    g.popMatrix();
  }
};

int main()
{
  MyApp app;
  app.dimensions(600, 400);
  app.start();
}
