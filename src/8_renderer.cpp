// SPDX-FileCopyrightText: 2026 Kon Hyong Kim <konhyong@gmail.com>
// SPDX-License-Identifier: BSD-3-Clause
#include "arg_workshop/8_renderer.hpp"

namespace odeon {
void Renderer::init(al::SearchPaths& searchPaths)
{
  shaderManager.setSearchPaths(searchPaths);
  shaderManager.add("eqr", "8_eqr.vert", "8_eqr.frag");

  cubeMap.filter(al::Texture::LINEAR);
  cubeMap.createCubemap(2048);

  rbo.resize(cubeMap.width(), cubeMap.height());

  fbo.bind();
  fbo.attachCubemapFace(cubeMap, GL_TEXTURE_CUBE_MAP_POSITIVE_X);
  fbo.attachRBO(rbo);
  fbo.unbind();

  quad.primitive(al::Mesh::TRIANGLE_STRIP);
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

void Renderer::update() { shaderManager.update(); }

void Renderer::draw(al::Graphics& g, int fbWidth, int fbHeight,
                    al::ShaderProgram* shader,
                    std::function<void(int)> captureFunc)
{
  fbo.bind();

  shader->use();

  for (int current_face = 0; current_face < 6; ++current_face) {
    fbo.attachCubemapFace(cubeMap,
                          GL_TEXTURE_CUBE_MAP_POSITIVE_X + current_face);
    g.pushViewport(0, 0, cubeMap.width(), cubeMap.height());

    captureFunc(current_face);

    g.popViewport();
  }

  fbo.unbind();

  g.clear(0);
  g.viewport(0, 0, fbWidth, fbHeight);

  auto& eqr_shader = shaderManager.get("eqr");
  eqr_shader.use();

  glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

  cubeMap.bind(0);
  eqr_shader.uniform("pixelMap", 0);
  quad.draw();

  cubeMap.unbind(0);
}
}  // namespace odeon