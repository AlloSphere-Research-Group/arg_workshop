// SPDX-FileCopyrightText: 2025 AlloSphere Research Group <allosphere@ucsb.edu>
// SPDX-License-Identifier: BSD-3-Clause
#include "al/app/al_App.hpp"
#include "al/graphics/al_Image.hpp"
#include "al/graphics/al_ShaderManager.hpp"
#include "al/graphics/al_Shapes.hpp"
#include "al/graphics/al_Texture.hpp"
#include "al/graphics/al_VAOMesh.hpp"

using namespace al;

struct MyApp : App {
  VAOMesh mesh;
  ShaderManager shaderManager;
  Texture texture;

  void onCreate() override
  {
    lens().near(0.1).far(25).fovy(45);
    nav().pos(0, 0, 4);

    SearchPaths searchPaths;
    searchPaths.addAppPaths();
    searchPaths.addRelativePath("shaders", false);
    searchPaths.addRelativePath("images", false);

    shaderManager.setSearchPaths(searchPaths);
    shaderManager.add("texture", "3_texture.vert", "3_texture.frag");

    // loadImage("path_to_image");
    loadImage(searchPaths.find("pattern.png").filepath());

    addTexSphere(mesh);
    mesh.update();
  }

  void loadImage(const std::string& imagePath)
  {
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
  }

  void onAnimate(double dt) override { shaderManager.update(); }

  void onDraw(Graphics& g) override
  {
    g.clear();
    g.depthTesting(true);
    
    auto& shader = shaderManager.get("texture");
    shader.use();

    // need to bind the texture object
    texture.bind(0);
    g.pushMatrix();
    shader.uniform("u_projMatrix", g.projMatrix());
    shader.uniform("u_viewMatrix", g.viewMatrix());
    shader.uniform("u_modelMatrix", g.modelMatrix());
    // send the binding point of the texture to the shader
    shader.uniform("u_imageTex", 0);
    mesh.draw();
    g.popMatrix();
    texture.unbind();
  }
};

int main()
{
  MyApp app;
  app.dimensions(600, 400);
  app.start();
}
