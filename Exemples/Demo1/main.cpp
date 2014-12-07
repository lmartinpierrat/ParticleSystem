//
// main.cpp for ParticleSystemDemo1 in /ParticleSystem/Exemples/Demo1
// 
// Made by Louis Martin-Pierrat
// Login   <mart_p@epitech.net>
// 
// Started on  Fri Oct 17 17:33:08 2014 Louis Martin-Pierrat
// Last update Fri Oct 17 18:29:17 2014 Louis Martin-Pierrat
//

#define		GLM_FORCE_RADIANS
#define		GLFW_INCLUDE_NONE
#include	<GLFW/glfw3.h>
#include	<iostream>
#include	<list>
#include	<cstdlib>
#include	<thread>
#include	<glbinding/Binding.h>
#include	<glbinding/gl/gl.h>

// glm::vec3, glm::vec4, glm::ivec4, glm::mat4
#include	<glm/glm.hpp>
// glm::perspective
#include	<glm/gtc/matrix_transform.hpp> 

#include	<ParticleSystem/ParticleSystem.hpp>

static void	errorCallback(int error, const char *description)
{
  std::cerr << "[GLFW] " << error << " : " << description << std::endl;
}

static void	keyCallback(GLFWwindow *window, int key,
			    __attribute__((unused))int scancode,
			    int action,
			    __attribute__((unused))int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

GLFWwindow	*initGlfwWindow(void)
{
  GLFWwindow	*window;

  if ((window = glfwCreateWindow(800, 600, "ParticleSystem - Demo1", NULL, NULL)) == NULL)
    return (NULL);
  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, keyCallback);
  return (window);
}

void				drawingScene(std::list<ParticleSystem::ParticleSystem *> &scene, const glm::mat4 &projection, const glm::mat4 &modelview, const glm::vec3 &camPosition)
{
  for (std::list<ParticleSystem::ParticleSystem *>::iterator it = scene.begin() ; it != scene.end() ; ++it)
    {
      (*it)->draw(projection, modelview, camPosition);
    }
}

void				updateScene(std::list<ParticleSystem::ParticleSystem *> &scene, float elapsedTime)
{
  for (std::list<ParticleSystem::ParticleSystem *>::iterator it = scene.begin() ; it != scene.end() ; ++it)
    {
      (*it)->update(elapsedTime);
    }
}

void				reinit(std::list<ParticleSystem::ParticleSystem *> &scene)
{
  for (std::list<ParticleSystem::ParticleSystem *>::iterator it = scene.begin() ; it != scene.end() ; ++it)
    {
      (*it)->reinit();
    }
}

void				initializeScene(std::list<ParticleSystem::ParticleSystem *> &scene)
{
  ParticleSystem::ParticleSystem	*engine = new ParticleSystem::ParticleSystem();

  engine->getRenderer()->getShader().loadFromFile("./Assets/Shaders/basic.vs", "./Assets/Shaders/basic.fs");
  scene.push_back(engine);
}

int						run_demo(void)
{
  GLFWwindow					*window = initGlfwWindow();
  std::list<ParticleSystem::ParticleSystem *>	scene;
  double					lastFrameTime = glfwGetTime();
  double					currentFrameTime = glfwGetTime();
  glm::vec3					camPosition = glm::vec3(0.0f, -5.0, 5.0f);

  if (window == NULL)
    return (EXIT_FAILURE);
  glbinding::Binding::initialize();

  initializeScene(scene);

  glm::mat4	projection = glm::perspective(60.0f, 800.0f / 600.0f, 0.1f, 100.0f);
  while (!glfwWindowShouldClose(window))
    {
      glm::mat4	modelview = glm::lookAt(camPosition, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
      lastFrameTime = currentFrameTime;
      currentFrameTime = glfwGetTime();

      gl::glClear(gl::GL_COLOR_BUFFER_BIT | gl::GL_DEPTH_BUFFER_BIT);

      std::thread updater(&updateScene, std::ref(scene), currentFrameTime - lastFrameTime);
      drawingScene(scene, projection, modelview, camPosition);
      updater.join();

      reinit(scene);

      camPosition = glm::vec3((int)(camPosition.x + 0.001) % 10, camPosition.y, camPosition.z);

      glfwSwapBuffers(window);
      glfwPollEvents();
    }
  return (EXIT_SUCCESS);
}

int	main(void)
{
  glfwSetErrorCallback(errorCallback);
  if (!glfwInit())
    return (EXIT_FAILURE);
  atexit(&glfwTerminate);
  return (run_demo());
}
