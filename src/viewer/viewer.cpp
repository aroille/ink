
#include "core/renderer.h"
#include "core/integrator.h"
#include "core/scene.h"
#include "core/film.h"
#include "core/camera.h"
#include "core/filter.h"
#include "core/shape.h"
#include "core/material.h"
#include "core/log.h"

#include <GLFW/glfw3.h>

using namespace ink;

int main(int, char**)
{
  if (!glfwInit())
  {
    INK_LOG("ERROR GLFW: initialization failed");
    return EXIT_FAILURE;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

  GLFWwindow* window = glfwCreateWindow(640, 480, "Lookout", NULL, NULL);
  if (!window)
  {
    INK_LOG("ERROR GLFW: create window or create opengl context failed");
    return EXIT_FAILURE;
  }

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  while (!glfwWindowShouldClose(window))
  {
    // render
    //glClear(GL_COLOR_BUFFER_BIT);

    // Swap front and back buffers
    glfwSwapBuffers(window);

    // Poll for and process events
    glfwPollEvents();
  }

  Scene scene;
  PinholeCamera camera;

  SimpleIntegrator integrator;
  integrator.max_bounce = 3;
  integrator.sky_radiance = Vec3f(0.0f, 0.0f, 0.0f);

  SimpleRenderer renderer;
  renderer.spp = 128;
  renderer.tile_size = 16;

  Film film(320, 320);
  BoxFilter filter(1.f);

  // start rendering
  renderer.start(integrator, scene, camera, film, filter);

  glfwTerminate();
   
  return EXIT_SUCCESS; 
}
