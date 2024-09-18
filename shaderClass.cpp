#include "shaderClass.h"

std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	//Create fragment shader object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);		//Gluint is GL's unsigned int

	//Now to connect the imported vertex shader to our GLuint vertax shader
	//glShaderSource(reference value, specifying that we are just using 1 string, point to the 
	// source code of vertex shader)
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	//The gpu cannot compile the souce code hence we need to compile the shader rn to machine code
	glCompileShader(vertexShader);


	//Now to do the smae process to fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	//Now to use these shaders, we need to wrap them up into something called shader program
	//glCreateProgram() is an OpenGL function used to create a shader program object.A 
	//shader program is a container that holds multiple shaders(like vertex and fragment shaders) 
	//and links them together into a single executable unit that the GPU can run.
	ID = glCreateProgram();

	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	glLinkProgram(ID);


	//Now that we have successfully created one shader, we have no use for vertex and ffragment shader
	//that we had previosly created........so to delete those
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}