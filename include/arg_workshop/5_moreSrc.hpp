// SPDX-FileCopyrightText: 2025 AlloSphere Research Group <allosphere@ucsb.edu>
// SPDX-License-Identifier: BSD-3-Clause
#pragma once

#include "al/graphics/al_Graphics.hpp"
#include "al/graphics/al_VAOMesh.hpp"

namespace exampleNamespace {
class Renderer {
 public:
  void init();
  void isValid();
  void update(double dt);
  void draw(al::Graphics& g);

 private:
  al::VAOMesh mesh;
  double phase{0.};
  double period{10.};
};
}  // namespace exampleNamespace
