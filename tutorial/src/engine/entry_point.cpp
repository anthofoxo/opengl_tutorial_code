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
	spdlog::set_level(spdlog::level::trace);

	spdlog::info("Hello spdlog!");

	glfwSetErrorCallback([](int error_code, const char* description)
		{
			spdlog::error("Glfw error {}: {}", error_code, description);
		});

	if(!glfwInit())
	{
		spdlog::critical("Glfw initialization failed");
		return EXIT_FAILURE;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_CONTEXT_NO_ERROR, GLFW_FALSE);
	GLFWwindow* window = glfwCreateWindow(1280, 720, "Hello Window", nullptr, nullptr);

	if (!window)
	{
		glfwTerminate();
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

	glClearColor(1.0f, 0.5f, 0.0f, 1.0f);

	// Create vao/vbo
	float data[] = { -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f };

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao); // This stays bound for our draw call
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	while(!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);
		// Draw call
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
	}

	// Delete objects
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);

	glfwDestroyWindow(window);
	glfwTerminate();
	spdlog::shutdown();
}