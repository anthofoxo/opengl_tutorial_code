#include <GLFW/glfw3.h>
#include <glad/gl.h>

int main()
{
	glfwInit();

	// Specify the settings to use for creating the OpenGL context.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	// Forces OpenGL to throw errors instead of causing undefined behavior.
	glfwWindowHint(GLFW_CONTEXT_NO_ERROR, GLFW_FALSE);

	// The window will be created with the specified settings.
	GLFWwindow* window = glfwCreateWindow(1280, 720, "Hello Window", nullptr, nullptr);

	// A context is created but must be made current to be able to use it
	glfwMakeContextCurrent(window);

	// Query the driver for all the OpenGL functions using the built-in glfw proc adress function.
	gladLoadGL(&glfwGetProcAddress);

	// At this point OpenGL has all it's function loaded an may be used.

	// Set the clear color to orange
	glClearColor(1.0f, 0.5f, 0.0f, 1.0f);

	while(!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		// Clear the color buffer
		glClear(GL_COLOR_BUFFER_BIT);

		// Swap the front and back buffers.
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();
}