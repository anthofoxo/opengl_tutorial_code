#include <GLFW/glfw3.h>

int main()
{
	// Initialize GLFW, this must be called before any other GLFW function
	glfwInit();

	// Create a window
	// Note since C++11 we can use nullptr instead of NULL
	GLFWwindow* window = glfwCreateWindow(1280, 720, "Hello Window", nullptr, nullptr);

	// Run the main loop until the user closes the window
	while (!glfwWindowShouldClose(window))
	{
		// Process events, such as keyboard input, resize, movement etc.
		glfwPollEvents();
	}

	// After the window is closed, destroy the window and terminate GLFW
	glfwDestroyWindow(window);
	glfwTerminate();
}