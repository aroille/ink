
#include "core/renderer.h"
#include "core/integrator.h"
#include "core/scene.h"
#include "core/film.h"
#include "core/camera.h"
#include "core/filter.h"
#include "core/shape.h"
#include "core/material.h"
#include "core/log.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../press/scene_samples.h"
#include <chrono>

using namespace ink;

struct Vertex
{
  float x, y;
  float u, v;
};

static const float vertexData[] =
{ //  X      Y       U     V
  -1.0f, -1.0f,   0.0f, 1.0f,
   1.0f, -1.0f,   1.0f, 1.0f,
   1.0f,  1.0f,   1.0f, 0.0f,
  -1.0f,  1.0f,   0.0f, 0.0f
};

static const char* vertex_shader_text =
  "#version 150 core\n"
  "in vec2 in_position;\n"
  "in vec2 in_texcoord;\n"
  "out vec2 texcoord;\n"
  "void main()\n"
  "{\n"
  "    gl_Position = vec4(in_position, 0.0, 1.0);\n"
  "    texcoord = in_texcoord;\n"
  "}\n\0";

static const char* fragment_shader_text =
  "#version 150 core\n"
  "in vec2 texcoord;\n"
  "out vec4 out_color;\n"
  "uniform sampler2D texsampler;\n"
  "void main()\n"
  "{\n"
  "    out_color = texture(texsampler, texcoord);\n"
  "    //out_color = vec4(texcoord, 0.0, 1.0);\n"
  "}\n\0";

static void error_glfw_callback(int error, const char* description)
{
  INK_LOG("ERROR GLFW: " << description);
}

using Time = std::chrono::high_resolution_clock;
using DurationMicro = std::chrono::duration<float, std::micro>;

int main(int, char**)
{
  Scene scene;
  PinholeCamera camera;
  create_cornell_box_scene(scene, camera);

  SimpleIntegrator integrator;
  integrator.max_bounce = 10;
  integrator.sky_radiance = Vec3f(0.7f, 0.7f, 0.7f);

  SimpleRenderer renderer;
  renderer.spp = 1;
  renderer.tile_size = 32;

  Film film(720, 720);
  BoxFilter filter(1.f);

  // start rendering
  GLFWwindow* window;
  GLuint vertex_buffer, vertex_shader, fragment_shader, program, texture;
  GLint position_location, texcoord_location, texsampler_location;;
  GLenum error;

  glfwSetErrorCallback(error_glfw_callback);

  if (!glfwInit())
  {
    INK_LOG("ERROR GLFW: initialization failed");
    exit(EXIT_FAILURE);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_RESIZABLE, false);

  window = glfwCreateWindow(film.width(), film.height(), "Inker", NULL, NULL);

  if (!window)
  {
    INK_LOG("ERROR GLFW: window creation failed");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window);
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  glfwSwapInterval(1);

  vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
  glCompileShader(vertex_shader);

  GLint vertex_param;
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &vertex_param);
  if (!vertex_param) 
  {
    GLchar log[4096];
    glGetShaderInfoLog(vertex_shader, sizeof(log), NULL, log);
    INK_LOG("VertexShader compilation error: " << (char *)log);
    exit(EXIT_FAILURE);
  }

  fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
  glCompileShader(fragment_shader);

  GLint frag_param;
  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &frag_param);
  if (!frag_param) 
  {
    GLchar log[4096];
    glGetShaderInfoLog(fragment_shader, sizeof(log), NULL, log);
    INK_LOG("FragmentShader compilation error: " << (char *)log);
    exit(EXIT_FAILURE);
  }

  program = glCreateProgram();
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);
  glLinkProgram(program);

  GLuint gVAO;
  glGenVertexArrays(1, &gVAO);
  glBindVertexArray(gVAO);

  GLuint gVBO;
  glGenBuffers(1, &gVBO);
  glBindBuffer(GL_ARRAY_BUFFER, gVBO);

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

  position_location = glGetAttribLocation(program, "in_position");
  texcoord_location = glGetAttribLocation(program, "in_texcoord");

  glEnableVertexAttribArray(position_location);
  glVertexAttribPointer(position_location, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)0);

  glEnableVertexAttribArray(texcoord_location);
  glVertexAttribPointer(texcoord_location, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)(sizeof(float) * 2));

  // create texture
  glActiveTexture(GL_TEXTURE0);
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  std::vector<Vec3f> data_copy(film.width() * film.height());
  //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, film.width(), film.height(), 0, GL_RGBA, GL_FLOAT, (void*)data_copy.data());
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  texsampler_location = glGetUniformLocation(program, "texsampler");
  glUniform1i(texsampler_location, 0);

  uint32 iteration_count = 0;
  while (!glfwWindowShouldClose(window))
  {
    iteration_count++;

    // render
    renderer.random_seed = iteration_count;

    RenderStats stats = { 0 };
    auto start = Time::now();
    renderer.start(integrator, scene, camera, film, filter, stats);
    auto duration = Time::now() - start;
    float tracingTime = DurationMicro(duration).count();

    // update window's title
    char windowTitle[1024];
    sprintf(windowTitle, "Inker - %.2f M/s - iteration %d - %.1f fps", stats.rayCount / tracingTime, iteration_count, 1000000 / tracingTime);
    glfwSetWindowTitle(window, windowTitle);

    // copy texture
    for (uint32_t i = 0, size = data_copy.size(); i < size; ++i)
      data_copy[i] = film.data_ptr()[i] / iteration_count;

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, film.width(), film.height(), 0, GL_RGBA, GL_FLOAT, (void*)data_copy.data());

    // display 
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    glViewport(0, 0, width, height);
    glClearColor(0, 0, 1, 1); // black
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program);
    glBindVertexArray(gVAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    // Swap front and back buffers
    glfwSwapBuffers(window);

    // Poll for and process events
    glfwPollEvents();
  }

  glfwTerminate();
   
  return EXIT_SUCCESS; 
}

