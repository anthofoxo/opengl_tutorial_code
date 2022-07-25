#ifdef _WIN32 // Only do this on windows
#	define WIN32_LEAN_AND_MEAN // Makes the windows header a bit smaller
#	define NOMINMAX // Do not define min or max in the windows headers
#	include <Windows.h>
#endif
#include <GLFW/glfw3.h>

#include <glad/gl.h>
#include <spdlog/spdlog.h>

int main()
{
	// spdlog default it's log level to trace, change it to trace so we can see all output.
	spdlog::set_level(spdlog::level::trace);

	// Say hello!
	spdlog::info("Hello spdlog!");

	glfwSetErrorCallback([](int error_code, const char* description)
		{
			spdlog::error("Glfw error {}: {}", error_code, description);
		});

	if(!glfwInit())
	{
		spdlog::critical("Glfw initialization failed");
		return EXIT_FAILURE; // When failure occurs, return a failure code
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_CONTEXT_NO_ERROR, GLFW_FALSE);
	GLFWwindow* window = glfwCreateWindow(1280, 720, "Hello Window", nullptr, nullptr);

	if (!window)
	{
		glfwTerminate(); // Terminate glfw before returning
		spdlog::critical("Failed to create window");
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGL(&glfwGetProcAddress))
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		spdlog::critical("Failed to obtain OpenGL functions");
		return EXIT_FAILURE;
	}

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