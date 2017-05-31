#pragma once

#include "core/scene.h"
#include "core/shape.h"

using namespace ink;

namespace helper
{
  void create_quad(SceneShape<TriangleMesh> mesh)
  {
    mesh->tri_count = 2;
    mesh->vertices.reset(new Vec3f[4]);
    mesh->indices.reset(new uint32[6]);
    mesh->vertices[0] = Vec3f(-0.5f, -0.5f, 0.f);
    mesh->vertices[1] = Vec3f(0.5f, -0.5f, 0.f);
    mesh->vertices[2] = Vec3f(0.5f, 0.5f, 0.f);
    mesh->vertices[3] = Vec3f(-0.5f, 0.5f, 0.f);
    mesh->indices[0] = 0;
    mesh->indices[1] = 1;
    mesh->indices[2] = 3;
    mesh->indices[3] = 1;
    mesh->indices[4] = 2;
    mesh->indices[5] = 3;
  }
}