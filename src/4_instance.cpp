// SPDX-FileCopyrightText: 2025 AlloSphere Research Group <allosphere@ucsb.edu>
// SPDX-License-Identifier: BSD-3-Clause
#include <cmath>
#include <vector>

#include "al/app/al_App.hpp"
#include "al/graphics/al_BufferObject.hpp"
#include "al/graphics/al_Image.hpp"
#include "al/graphics/al_ShaderManager.hpp"
#include "al/graphics/al_Shapes.hpp"
#include "al/graphics/al_Texture.hpp"
#include "al/graphics/al_VAOMesh.hpp"

using namespace al;

// use this instead of static const
inline constexpr unsigned int g_instanceNum = 500;
// inline constexpr unsigned int g_instanceNum = 500000;

struct MyApp : App {
  VAOMesh mesh;
  ShaderManager shaderManager;
  Texture texture;
  BufferObject buffer;  // VBO
  std::vector<Vec3f> meshPositions;
  double time{0};

  void onCreate() override
  {
    lens().near(0.1).far(100).fovy(45);
    nav().pos(0, 0, 4);

    SearchPaths searchPaths;
    searchPaths.addAppPaths();
    searchPaths.addRelativePath("shaders", false);
    searchPaths.addRelativePath("images", false);

    shaderManager.setSearchPaths(searchPaths);
    shaderManager.add("instance", "4_instance.vert", "4_instance.frag");

    // loadImage("path_to_image");
    loadImage(searchPaths.find("pattern.png").filepath());

    addTexSphere(mesh, 1);
    mesh.update();

    // initializing VBO
    // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBufferData.xhtml
    buffer.bufferType(GL_ARRAY_BUFFER);  // standard for VBO
    buffer.usage(GL_STATIC_DRAW);        // modified once, used for drawing
    // buffer.usage(GL_DYNAMIC_DRAW);  // modified frequently, used for drawing
    buffer.create();

    // configuring mesh's VAO and pointing to the VBO
    // check al_VAOMesh.hpp for details
    auto& meshVAO = mesh.vao();
    meshVAO.bind();
    meshVAO.enableAttrib(4);
    meshVAO.attribPointer(4, buffer, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribDivisor(4, 1);

    meshPositions.resize(g_instanceNum);

    // for static draw
    float inverse = 1.f / (float)g_instanceNum;
    for (unsigned int i = 0; i < g_instanceNum; ++i) {
      meshPositions[i] = Vec3f(100 * (i * inverse) * std::cos(i),
                               100 * (i * inverse) * std::sin(i), 0);
    }

    buffer.bind();
    buffer.data(meshPositions.size() * 3 * sizeof(float), meshPositions.data());
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

    texture.filter(Texture::LINEAR);
    texture.create2D(imageData.width(), imageData.height());
    texture.submit(imageData.array().data(), GL_RGBA,
                   GL_UNSIGNED_INT_8_8_8_8_REV);
  }

  void onAnimate(double dt) override
  {
    shaderManager.update();

    time += dt;

    // for dynamic draw
    // float inverse = 1.f / (float)g_instanceNum;
    // for (unsigned int i = 0; i < g_instanceNum; ++i) {
    //   meshPositions[i] =
    //       Vec3f(100 * (i * inverse) * std::cosf(10.f * i * inverse * time),
    //             100 * (i * inverse) * std::sinf(10.f * i * inverse * time),
    //             0);
    // }

    // buffer.bind();
    // buffer.data(meshPositions.size() * 3 * sizeof(float),
    // meshPositions.data());
  }

  void onDraw(Graphics& g) override
  {
    g.clear();
    g.depthTesting(true);

    texture.bind(0);

    auto& shader = shaderManager.get("instance");
    shader.use();

    shader.uniform("u_projMatrix", g.projMatrix());
    shader.uniform("u_viewMatrix", g.viewMatrix());
    shader.uniform("u_modelMatrix", g.modelMatrix());
    shader.uniform("u_imageTex", 0);

    // instanced rendering
    mesh.vao().bind();
    mesh.indexBuffer().bind();  // needed for mesh using indices
    // raw openGL call for instanced rendering
    // for non-indexed meshes, use glDrawArraysInstanced instead
    glDrawElementsInstanced(GL_TRIANGLES, mesh.indices().size(),
                            GL_UNSIGNED_INT, 0, meshPositions.size());

    // // non-instanced rendering
    // for (int i = 0; i < g_instanceNum; ++i) {
    //   g.pushMatrix();
    //   g.translate(meshPositions[i]);
    //   shader.uniform("u_modelMatrix", g.modelMatrix());
    //   mesh.draw();
    //   g.popMatrix();
    // }

    texture.unbind();
  }
};

int main()
{
  MyApp app;
  app.dimensions(600, 400);
  app.start();
}
