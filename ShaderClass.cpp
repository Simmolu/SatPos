#include "ShaderClass.h"


// Function to read the contents of a file into a std::string
std::string get_file_contents(const char* filename)
{
    // Open the file with the given filename in binary mode
    std::ifstream in(filename, std::ios::binary);

    // Check if the file was successfully opened
    if (in)
    {
        std::string contents; // String to hold the file contents

        // Move the file read position to the end to determine the file size
        in.seekg(0, std::ios::end);

        // Resize the string to fit the entire file content
        contents.resize(in.tellg());

        // Move the file read position back to the beginning
        in.seekg(0, std::ios::beg);

        // Read the entire file content into the string
        in.read(&contents[0], contents.size());

        // Close the file stream
        in.close();

        // Return the contents of the file
        return(contents);
    }

    // If the file couldn't be opened, throw an error with the current errno value
    throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile) {
    std::string vertexCode = get_file_contents(vertexFile);
    std::string fragmentCode = get_file_contents(fragmentFile);

    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

	//create vertex shader object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//attach vertex shader source to the vertex shader object
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	//compile the vertex shader into machine code
	glCompileShader(vertexShader);


	// create fragment shader object and get its reference
	GLuint fragmentShaderOne = glCreateShader(GL_FRAGMENT_SHADER);
	//attach fragment shader source to the fragment shader object
	glShaderSource(fragmentShaderOne, 1, &fragmentSource, NULL);
	//compile fragment shader into machine code
	glCompileShader(fragmentShaderOne);

	//create our shader program object and get its reference
	ID = glCreateProgram();
	//attach vertex and fragment shaders to shader program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShaderOne);
	//wrap up/link all shaders together into the shader program
	glLinkProgram(ID);

	//delete the now useless vertex/fragment shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShaderOne);
}


void Shader::Activate()
{
    glUseProgram(ID);
}

void Shader::Delete()
{
    glDeleteProgram(ID);
}