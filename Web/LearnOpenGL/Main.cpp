#include "../../shared/Source/Utility.h"
static GLFWwindow* window;

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void initGlfw()
{
	glfwInit();
	// set OpenGL ver (WebGL 2.0)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
}

int createWindow()
{
	window = glfwCreateWindow(windowsWidth, windowsHeight, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		printf("Failed to create GLFW window\n");
		glfwTerminate();
		return 0;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);	// register callback for on windows resize event
	return 1;
}

void createViewport()
{
	glViewport(0, 0, windowsWidth, windowsHeight);
}

void initInput()
{
	// glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetKeyCallback(window, key_callback);
}

void initOpenGLSettings()
{
	// opengl rendering configurations
	// depth ordering on OpenGL
	glEnable(GL_DEPTH_TEST);
	// alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// cull face (discard unseen faces, save 50% on fragment shader runs)
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);
}

int main()
{
	initGlfw();
	createWindow();
	createViewport();
	initInput();
	initOpenGLSettings();
	printf("OSEngine initialized\n");
}