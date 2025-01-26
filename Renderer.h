#ifndef RENDERER_H
#define RENDERER_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>	
#include "ShaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

//Need to have an initialize function for the renderer that initializes glad, the window, glfw, etc. 


class Renderer
{
private:
	GLFWwindow* mrScreen;
	Shader shaderPrgm;
	VAO VAO1;
	VBO VBO1;
	VBO VBO2;
	EBO EBO1;

public:
	Renderer();

	void shaderInitialize();
	void renderMainLoop(GLFWwindow* mrScreen);

	void terminateRenderer();
};



#endif 

