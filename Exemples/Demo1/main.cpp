//
// main.cpp for ParticleSystemDemo1 in /ParticleSystem/Exemples/Demo1
// 
// Made by Louis Martin-Pierrat
// Login   <mart_p@epitech.net>
// 
// Started on  Fri Oct 17 17:33:08 2014 Louis Martin-Pierrat
// Last update Fri Oct 17 18:29:17 2014 Louis Martin-Pierrat
//

#define		GLFW_INCLUDE_NONE
#include	<GLFW/glfw3.h>
#include	<glbinding/Binding.h>

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

  if ((window = glfwCreateWindow(500, 500, "ParticleSystem - Demo1", NULL, NULL)) == NULL)
    return (NULL);
  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, keyCallback);
  return (window);
}

void	drawingScene(std::list<ParticleSystem *> &scene)
{
  for (std::list<ParticleSystem *>::iterator it = scene.begin() ; it != scene.end() ; ++it)
    {
      (*it)->draw();
    }
}

void	updateScene(std::list<ParticleSystem *> &scene)
{
  for (std::list<ParticleSystem *>::iterator it = scene.begin() ; it != scene.end() ; ++it)
    {
      (*it)->update();
    }
}

void	initializeScene(std::list<ParticleSystem *> &scene)
{
  scene.push_back(new ParticleSystem());
}

int	run_demo(void)
{
  GLFWwindow	window = initGlfwWindow();
  std::list<ParticleSystem *>	scene;

  if (window == NULL)
    return (EXIT_FAILURE);
  glbinding::Binding::initialize();
  initializeScene(scene);
  while (!glfwWindowShouldClose(window))
    {
      std::thread drawer(&drawingScene, scene);
      std::thread updater(&updateScene, scene);
      drawer.join();
      updater.join();
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
