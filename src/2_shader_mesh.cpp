// SPDX-FileCopyrightText: 2025 AlloSphere Research Group <allosphere@ucsb.edu>
// SPDX-License-Identifier: BSD-3-Clause
#include "al/app/al_App.hpp"
#include "al/graphics/al_ShaderManager.hpp"
#include "al/graphics/al_Shapes.hpp"
#include "al/graphics/al_VAOMesh.hpp"

using namespace al;

struct MyApp : App {
  VAOMesh mesh;
  ShaderManager shaderManager;

  void onCreate() override
  {
    lens().near(0.1).far(25).fovy(45);
    nav().pos(0, 0, 4);

    SearchPaths searchPaths;
    searchPaths.addAppPaths();
    searchPaths.addRelativePath("shaders", false);

    shaderManager.setSearchPaths(searchPaths);
    shaderManager.add("mesh", "2_mesh.vert", "2_mesh.frag");

    addTexSphere(mesh);
    mesh.update();
  }

  void onAnimate(double dt) override { shaderManager.update(); }

  void onDraw(Graphics& g) override
  {
    g.clear();
    g.depthTesting(true); // false by default
    
    auto& shader = shaderManager.get("mesh");
    shader.use();

    // maintains stack of model matrix
    g.pushMatrix();
    shader.uniform("u_projMatrix", g.projMatrix());
    shader.uniform("u_viewMatrix", g.viewMatrix());
    g.translate(1.f, 0, 0); // modifies model matrix. SRT
    shader.uniform("u_modelMatrix", g.modelMatrix());
    mesh.draw();
    g.popMatrix();
  }
};

int main()
{
  MyApp app;
  app.dimensions(600, 400);
  app.start();
}
