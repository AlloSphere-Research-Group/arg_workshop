// SPDX-FileCopyrightText: 2026 AlloSphere Research Group <allosphere@ucsb.edu>
// SPDX-License-Identifier: BSD-3-Clause
#include "al/app/al_DistributedApp.hpp"
#include "al/graphics/al_Shapes.hpp"
#include "al/graphics/al_VAOMesh.hpp"
#include "al/spatial/al_Pose.hpp"
#include "al/ui/al_ParameterGUI.hpp"

using namespace al;

struct MyApp : DistributedApp {
  VAOMesh mesh;
  ParameterPose pose{"pose", "sphere"};
  Parameter phase{"phase", "sphere", 0.f, 0.f, 1.f};
  Parameter period{"period", "sphere", 10.f, 0.1f, 100.f};
  ParameterColor color{"color", "sphere", Color(1.f, 0.5f, 0.5f)};

  void onCreate() override
  {
    lens().near(0.1).far(25).fovy(45);
    nav().pos(0, 0, 4);

    addTetrahedron(mesh);
    mesh.update();

    parameterServer() << pose << phase << period << color;

    if (isPrimary()) {
      imguiInit();
    }
  }

  void onAnimate(double dt) override
  {
    if (isPrimary()) {
      pose.set(nav());
    }
    else {
      nav().set(pose.get());
    }

    phase.set(phase.get() + dt / period.get());
    if (phase.get() >= 1.f) phase.set(phase.get() - 1.f);

    if (isPrimary()) {
      imguiBeginFrame();
      ImGui::Begin("Sphere Parameters");
      ParameterGUI::draw(&pose);
      ParameterGUI::draw(&phase);
      ParameterGUI::draw(&period);
      ParameterGUI::draw(&color);
      ImGui::End();
      imguiEndFrame();
    }
  }

  void onDraw(Graphics& g) override
  {
    g.clear(0, 0, 0);

    g.pushMatrix();
    g.rotate(phase.get() * 360, 0, 1, 0);
    g.color(color.get());
    g.draw(mesh);
    g.popMatrix();

    if (isPrimary()) {
      imguiDraw();
    }
  }

  void onExit() override
  {
    if (isPrimary()) {
      imguiShutdown();
    }
  }
};

int main()
{
  MyApp app;
  app.dimensions(600, 400);
  app.start();
}
