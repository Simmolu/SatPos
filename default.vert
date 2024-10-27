//open gl doesn't provide vertex and fragment shaders for rendering, we write our own.

#version 330 core
layout (location = 0)  in vec3 aPos;
void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
};
