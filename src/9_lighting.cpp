// SPDX-FileCopyrightText: 2026 AlloSphere Research Group <allosphere@ucsb.edu>
// SPDX-License-Identifier: BSD-3-Clause
#include "al/app/al_DistributedApp.hpp"
#include "al/graphics/al_Image.hpp"
#include "al/graphics/al_ShaderManager.hpp"
#include "al/graphics/al_Shapes.hpp"
#include "al/graphics/al_Texture.hpp"
#include "al/graphics/al_VAOMesh.hpp"
#include "al/ui/al_ParameterGUI.hpp"

using namespace al;

struct SphereApp : DistributedApp {
  VAOMesh mesh;
  Texture texture;
  ShaderManager shaderManager;

  ParameterPose pose{"pose", ""};
  Parameter doorAngle{"doorAngle", "", 0.f, 0.f, 120.f};
  ParameterColor lightColor{"lightColor", "", Color(0.5f, 0.5f, 0.5f)};

  void onCreate() override
  {
    lens().near(0.1).far(25).fovy(45);
    nav().pos(0, 0, 4);

    SearchPaths searchPaths;
    searchPaths.addAppPaths();
    searchPaths.addRelativePath("shaders", false);
    searchPaths.addRelativePath("images", false);

    shaderManager.setSearchPaths(searchPaths);
    shaderManager.add("lighting", "9_lighting.vert", "9_lighting.frag");

    const auto& imagePath = searchPaths.find("pattern.png").filepath();

    auto imageData = Image(imagePath);
    if (imageData.array().size() > 0) {
      std::cout << "Loaded image: " << imagePath << std::endl;
    }
    else {
      std::cerr << "Failed to load image: " << imagePath << std::endl;
      return;
    }

    // create a texture object on the gpu with the image resolution
    // image loads in 4 channels
    texture.filter(Texture::LINEAR);
    texture.create2D(imageData.width(), imageData.height());
    // GL_RGBA8 is the typical choice, but this is faster on some machines
    texture.submit(imageData.array().data(), GL_RGBA,
                   GL_UNSIGNED_INT_8_8_8_8_REV);

    addCuboid(mesh, 5.f, 4.f, 15.f, true);
    mesh.update();

    parameterServer() << pose << doorAngle << lightColor;

    if (isPrimary()) {
      imguiInit();
    }
  }

  void onExit() override
  {
    if (isPrimary()) {
      imguiShutdown();
    }
  }

  void onAnimate(double dt) override
  {
    shaderManager.update();

    if (isPrimary()) {
      pose.set(nav());
    }
    else {
      nav().set(pose.get());
    }

    // animate doorAngle here if needed

    if (isPrimary()) {
      imguiBeginFrame();
      ImGui::Begin("Sphere Parameters");
      // ParameterGUI::draw(&pose);
      ParameterGUI::draw(&doorAngle);
      ParameterGUI::draw(&lightColor);
      ImGui::End();
      imguiEndFrame();
    }
  }

  void onDraw(Graphics& g) override
  {
    g.clear(0, 0, 0);
    g.depthTesting(true);

    auto& shader = shaderManager.get("lighting");
    shader.use();

    texture.bind(0);
    g.pushMatrix();

    shader.uniform("u_modelMatrix", g.modelMatrix());
    shader.uniform("u_viewMatrix", g.viewMatrix());
    shader.uniform("u_projMatrix", g.projMatrix());
    shader.uniform("u_eyeSep", lens().eyeSep());
    shader.uniform("u_focLen", lens().focalLength());
    shader.uniform("u_doorAngle", doorAngle.get());
    shader.uniform("u_lightColor", lightColor.get());
    shader.uniform("u_imageTex", 0);
    mesh.draw();

    g.popMatrix();
    texture.unbind();

    if (isPrimary()) {
      imguiDraw();
    }
  }
};

int main()
{
  SphereApp app;
  app.dimensions(600, 400);
  app.start();
}
