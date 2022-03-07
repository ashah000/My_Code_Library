#include "Window.h"

Window::Window()
{
	width = 800;
	height = 600;
	bufferWidth = 0;
	bufferHeight = 0;
}

Window::Window(GLint WindowWidth, GLint WindowHeight)
{
	width = WindowWidth;
	height = WindowHeight;
	bufferWidth = 0;
	bufferHeight = 0;
}

int Window::Initialise()
{
	//Initialise GLFW
	if (!glfwInit())
	{
		printf("GLFW initialization Failed!");
		glfwTerminate();
		return 1;
	}

	//Setup GLFW Window Property
	// OpenGL Version (3.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Means No Backward Compatibility - Only Forward Compatibility.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // will throw error for deprecated functions being ported.
																   //Allow Forward Compatibility.
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	mainWindow = glfwCreateWindow(width, height, "Test Window", NULL, NULL);
	if (!mainWindow)
	{
		printf("GLFW Window cration failed");
		glfwTerminate();
		return 1;
	}

	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//set Context for glew to use, you can change it..
	glfwMakeContextCurrent(mainWindow);

	//Enable modern Extensions Features.
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("GLEW INITIALIZATION FAILED");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST);
	//setup Viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);
	return 0;
}

Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}
