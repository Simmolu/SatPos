#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>	

//open gl doesn't provide vertex and fragment shaders for rendering, we write our own.
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0)  in vec3 aPos;\n"
"void main()\n"
"{\n"
"    gl_position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";


int main() {

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

	//pixels are drawn from top left to bottom right in left to right then row order
	glViewport(0, 0, 800, 800);



	//create vertex shader object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//attach vertex shader source to the vertex shader object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//compile the vertex shader into machine code
	glCompileShader(vertexShader);


	// create fragment shader object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//attach fragment shader source to the fragment shader object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//compile fragment shader into machine code
	glCompileShader(fragmentShader);


	//create our shader program object and get its reference
	GLuint shaderProgram = glCreateProgram();
	//attach vertex and fragment shaders to shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	//wrap up/link all shaders together into the shader program
	glLinkProgram(shaderProgram);

	//delete the now useless vertex/fragment shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);




	//create our vertex coordinates
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, //lower left
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, //lower right
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f //top
	};

	//vertex buffer and array objects
	GLuint VAO, VBO;

	// generate our objects with only 1 object each ORDER MATTERS
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	
	//make VAO current vertex array object by binding it
	glBindVertexArray(VAO);

	//bind the VBO specifying its a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//configure the vertex attribute so that openGL knows how to read the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// enable the vertex attribute so that openGL knows how to use it
	glEnableVertexAttribArray(0);

	//bind both the VBO and VAO to 0 so that we dont accidentally modify VAO/VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);




	//each image drawn is called a frame
	//while screen loads pixels from current frame and displays, the next frame is being prepared in background
	//then when the next frame is called, the previous frame is drawn over and the cycle repeats. These are called front/back buffers
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(mrScreen);

	//core window loop, event polling
	while (!glfwWindowShouldClose(mrScreen)) {

		//specify color of background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		//clean back buffer, assign new color
		glClear(GL_COLOR_BUFFER_BIT);
		//tell openGL what shader program to use
		glUseProgram(shaderProgram);
		//bind VAO that opengl uses
		glBindVertexArray(VAO);
		//draw triangle using GL_TRIANGLES primitve
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(mrScreen);

		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	//closeout
	glfwDestroyWindow(mrScreen);
	glfwTerminate();

	return 0;
}