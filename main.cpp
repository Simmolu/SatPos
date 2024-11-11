#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>	
#include "ShaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Requests.h"


//what this teaches me is EITHER i need to have shaders for every primary color (likely) or have dynamic shaders that can be modified on the fly


int main() {

	Requests squire;

	std::cout << "Return data: " << squire.SatTLE("25544");

	//create our vertex coordinates

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



	glfwInit();

	//version info for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//create window object for glfw to manipulate
	
	
	GLFWwindow* mrScreen = glfwCreateWindow(800, 800, "SatPos", NULL, NULL);

	//window error catch
	if (mrScreen == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	//context for openGL
	glfwMakeContextCurrent(mrScreen);

	gladLoadGL();

	Shader shaderProgram("default.vert", "default.frag");
	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VBO VBO2(verticestwo, sizeof(verticestwo));

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

	//core window loop, event polling
	while (!glfwWindowShouldClose(mrScreen)) {

		//specify color of background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		//clean back buffer, assign new color
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.Activate();
		//bind VAO that opengl uses
		VAO1.Bind();
		//draw triangle using GL_TRIANGLES primitve
		glDrawArrays(GL_TRIANGLES, 0, 3);


		glfwSwapBuffers(mrScreen);

		glfwPollEvents();
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	//closeout
	glfwDestroyWindow(mrScreen);
	glfwTerminate();

	return 0;
}





/*So if I wanted to compartmentialize all of this rendering and get my own triangle, line, circle shapes etc I'd just need a function that takes in the size and shape you want, and then have dedicated functions for translating entities.*/