// SPDX-FileCopyrightText: 2025 AlloSphere Research Group <allosphere@ucsb.edu>
// SPDX-License-Identifier: BSD-3-Clause
#include "al/app/al_App.hpp"
#include "moreSrc.hpp"  // different header files
// path can be included in target_include_directories
// cpp=translation unit=src files need to specified in add_executable

using namespace al;

struct MyApp : App {
  // defined in moreSrc.hpp
  // namespaces can be useful for organization
  exampleNamespace::Renderer renderer;

  void onCreate() override
  {
    lens().near(0.1).far(25).fovy(45);
    nav().pos(0, 0, 4);

    renderer.init();
    renderer.isValid();
  }

  void onAnimate(double dt) override { renderer.update(dt); }

  void onDraw(Graphics& g) override { renderer.draw(g); }
};

int main()
{
  MyApp app;
  app.dimensions(600, 400);
  app.start();
}
