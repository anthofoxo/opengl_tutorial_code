#include <GLFW/glfw3.h>
#include <glad/gl.h>
#include <spdlog/spdlog.h>

int main()
{
	// spdlog default it's log level to trace, change it to trace so we can see all output.
	spdlog::set_level(spdlog::level::trace);

	// Say hello!
	spdlog::info("Hello spdlog!");

	// Window and context creation code
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_CONTEXT_NO_ERROR, GLFW_FALSE);
	GLFWwindow* window = glfwCreateWindow(1280, 720, "Hello Window", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	gladLoadGL(&glfwGetProcAddress);

	// OpenGL setup
	glClearColor(1.0f, 0.5f, 0.0f, 1.0f);

	// Main loop
	while(!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
	}

	// Shutdown glfw
	glfwDestroyWindow(window);
	glfwTerminate();

	// After program exits, it's not a bad idea to explicitly shutdown spdlog
	spdlog::shutdown();
}