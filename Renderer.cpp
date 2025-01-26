#include "Renderer.h"

Renderer::Renderer()
{
	glfwInit();

	//version info for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//create window object for glfw to manipulate


	mrScreen = glfwCreateWindow(800, 800, "SatPos", NULL, NULL);

	//window error catch
	if (mrScreen == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		//error handling in constructor or create seperate init function
	}
	//context for openGL
	glfwMakeContextCurrent(mrScreen);

	gladLoadGL();

	shaderPrgm = Shader("default.vert", "default.frag");
	VAO1 = VAO();
	VAO1.Bind();

	GLfloat vertices[] =
	{
		 -0.75f, -0.5f, 0.0f,
		 -0.25f, -0.5f, 0.0f,
		 -0.5f,  0.00f, 0.0f
	};

	GLfloat verticestwo[] =
	{
		 -0.25f, -0.5f, 0.0f,
		  0.25f, -0.5f, 0.0f,
		  0.0f,  0.00f, 0.0f
	};

	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	VBO1 = VBO(vertices, sizeof(vertices));
	EBO1 = EBO(indices, sizeof(indices));

	VBO2 = VBO(verticestwo, sizeof(verticestwo));
}

void Renderer::shaderInitialize()
{

	


	VAO1.LinkVBO(VBO1, 0);
	VAO1.Unbind();
	VBO1.Bind();
	EBO1.Unbind();

	//pixels are drawn from top left to bottom right in left to right then row order
	glViewport(0, 0, 800, 800);


	//each image drawn is called a frame
	//while screen loads pixels from current frame and displays, the next frame is being prepared in background
	//then when the next frame is called, the previous frame is drawn over and the cycle repeats. These are called front/back buffers
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::renderMainLoop(GLFWwindow* mrScreen)
{
	while (!glfwWindowShouldClose(mrScreen)) {

		//specify color of background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		//clean back buffer, assign new color
		glClear(GL_COLOR_BUFFER_BIT);

		shaderPrgm.Activate();
		//bind VAO that opengl uses
		VAO1.Bind();
		//draw triangle using GL_TRIANGLES primitve
		glDrawArrays(GL_TRIANGLES, 0, 3);


		glfwSwapBuffers(mrScreen);

		glfwPollEvents();
	}
}

void Renderer::terminateRenderer()
{
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderPrgm.Delete();

	//closeout
	glfwDestroyWindow(mrScreen);
	glfwTerminate();
}


