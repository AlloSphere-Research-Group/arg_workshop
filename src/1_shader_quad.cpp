// SPDX-FileCopyrightText: 2025 AlloSphere Research Group <allosphere@ucsb.edu>
// SPDX-License-Identifier: BSD-3-Clause
#include "al/app/al_App.hpp"
#include "al/graphics/al_ShaderManager.hpp"
#include "al/graphics/al_VAOMesh.hpp"

using namespace al;

struct MyApp : App {
  VAOMesh quad;
  ShaderManager shaderManager;

  double time{0.};
  float oscillator{1.f};

  void onCreate() override
  {
    lens().near(0.1).far(25).fovy(45);
    nav().pos(0, 0, 4);

    // class managing filesystem
    // to be replaced with std::filesystem
    SearchPaths searchPaths;
    searchPaths.addAppPaths();
    searchPaths.addRelativePath("shaders", false);

    shaderManager.setSearchPaths(searchPaths);
    shaderManager.add("quad", "1_quad.vert", "1_quad.frag");

    quad.primitive(Mesh::TRIANGLE_STRIP);
    quad.vertex(-1.f, -1.f, 0);
    quad.vertex(1.f, -1.f, 0);
    quad.vertex(-1.f, 1.f, 0);
    quad.vertex(1.f, 1.f, 0);
    quad.texCoord(0, 0);
    quad.texCoord(1, 0);
    quad.texCoord(0, 1);
    quad.texCoord(1, 1);
    quad.update();
  }

  void onAnimate(double dt) override
  {
    // allows real-time compilation of shaders
    shaderManager.update();

    time += dt;
    oscillator = std::cos(time * 0.5);
  }

  void onDraw(Graphics& g) override
  {
    g.clear();

    auto& shader = shaderManager.get("quad");
    shader.use();
    shader.uniform("u_osc", oscillator);

    // bypassing graphics class with direct rendering calls
    // no projection involved
    quad.draw();
  }
};

int main()
{
  MyApp app;
  app.dimensions(600, 400);
  app.start();
}
