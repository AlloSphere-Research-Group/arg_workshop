// SPDX-FileCopyrightText: 2026 Kon Hyong Kim <konhyong@gmail.com>
// SPDX-License-Identifier: BSD-3-Clause
#pragma once

#include <functional>

#include "al/graphics/al_FBO.hpp"
#include "al/graphics/al_Graphics.hpp"
#include "al/graphics/al_ShaderManager.hpp"
#include "al/graphics/al_Texture.hpp"
#include "al/graphics/al_VAOMesh.hpp"
#include "al/io/al_File.hpp"

namespace odeon {
struct Renderer {
  al::ShaderManager shaderManager;

  al::FBO fbo;
  al::RBO rbo;
  al::Texture cubeMap;

  al::VAOMesh quad;

  void init(al::SearchPaths& searchPaths);

  void update();

  void draw(al::Graphics& g, int fbWidth, int fbHeight,
            al::ShaderProgram* shader, std::function<void(int)> captureFunc);
};
}  // namespace odeon