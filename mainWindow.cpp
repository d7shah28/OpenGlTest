
#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"


int main()
{
	//Inititate glfw...................we also need to then stop glfw later
	glfwInit();		

	//application would work with open gl version 3 or 3.1,3.2, 3.3........ but wont work with verion 4
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);		

	//would not work with lower then 3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);		

	//removes depriciated features
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//new float GLfloat...normal float can be used but the size may differ from glfloat and hence 
	// minor data loss may occur
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,  // Left vertex
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,  // Right vertex
		0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,  // Top vertex
		-0.5f / 2, 0.5f*float(sqrt(3))/6,0.0f,	//Inner Left
		0.5f / 2, 0.5f*float(sqrt(3))/6,0.0f,	//Inner Right
		0.0f, -0.5f*float(sqrt(3))/3,0.0f	//Inner Down
	};

	GLuint indices[] =
	{
		0,3,5,	//Lower left triangle
		3,2,4,	//Lower right triangle
		5,4,1	//Upper triangle
	};

	//Created new window with variable name window and window name
	GLFWwindow* window = glfwCreateWindow(800, 800, "MyWindowBitches", NULL, NULL);	

	// if window fails
	if (window == NULL)
	{
		//Throw error
		std::cout << "Failed to create GLFW window" << std::endl;

		//Terminate glfw
		glfwTerminate();
		return -1;		//this indicates error or failure
	}

	// make window your primary window....if u dont do this, open gl with not do anything as it does 
	// not have any idea where it is supposed to show all its output
	glfwMakeContextCurrent(window);	

	//initializes all the function pointers that OpenGL will use. It must be called after creating 
	// the OpenGL context, typically after initializing your window with GLFW or another windowing 
	// system.
	gladLoadGL();		
	
	//defines the portion of the window where OpenGL will render.........sets x=0,y=0 to x=800,y=800
	glViewport(0, 0, 800, 800);		

	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkVBO(VBO1, 0);
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


	//Now that our shaders are done we need to create the 3d model with the array. the process of 
	//sending data to the graphics card is slow, so we need to send the data into big batches 
	//These big batches are called buffers, not to confuse with fornt and back buffer

	//Vertex Buffer Object(VBO)
	//A Vertex Buffer Object is an OpenGL object used to efficiently store 
	//vertex data(such as positions, colors, normals, and texture coordinates) on the GPU.
	//VBOs are crucial for optimizing rendering performance because they allow you to send large amounts
	//of data to the GPU and keep it there, reducing the need for frequent data transfers between 
	//the CPU and GPU.
	
	//the graphics card doesnt know the location of a VBO, in order to do that we make use of another 
	//object called th Vertex Array Object(VAO).
	//A VAO stores pointers to one or more VBOs
	//VAOs exist to quickly switch between multiple VBOs

	//GLuint VAO,VBO,EBO;

	// Generate and bind VAO first to set up vertex attribute pointers and state.
	// Then generate and bind VBO to upload vertex data.
	// This way, VAO captures the configuration of VBOs and vertex attributes.


	//glGenVertexArrays(1, &VAO);

	// to generate one or more buffer object names, which you can then use to manage vertex data, 
	//index data, and other types of buffer data.


	//glGenBuffers(1, &VBO);		//1 here represtents just one object to draw


	//glGenBuffers(1, &EBO);

	//Make VAO the current Vertex Object by binding it


	//glBindVertexArray(VAO);

	//Binding in open Gl means we make a certain object, our current object.
	//Whenever we fire a command to the buffer object, this object that is the current buffer will get
	//affected by it


	//glBindBuffer(GL_ARRAY_BUFFER, VBO);		//for vertices, we use array buffer

	////Now to store our vertices in the VBO
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//attribute is a way to communicate with the vertex shader from the outside
	//(pos of the vertAtribu,
	//values per vertex,
	//data type for values,
	//amount of data between each vertex,
	//offset[where our verices begin in the array])



	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),(void*)0);
	//glEnableVertexAttribArray(0);	//0 as our start pos is 0

	//Now just to keep thigs clean, we bind are VAO and VBO to 0
	//Blind VBO VAO and EBO to 0 so that we do not accidently modify it
	
	
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	/*Buffer(Fornt and back) -
		after a frame shows up in display, it goes in the background to allow newer frame to display.
		Now the older frame in bg has to be overwritten for display with new information.
		These two frames are called buffer.
		They are just a simple way of storage for pixels.
		The frame that is at front is called front buffer.
		The frame at the back is called the back buffer.*/

	//Color used to clear the frames in RGBA format
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);	

	//used to clear Color Buffer....then fill the screen with color specified by glClearColor
	glClear(GL_COLOR_BUFFER_BIT);		
	glfwSwapBuffers(window);

	//while the window is running
	while (!glfwWindowShouldClose(window))		
	{
		//Specify the color of the bf
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		//Clean back buffer and assign new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		//Tell openGL which shader program we want to use
		shaderProgram.Activate();
		//bind VAO so openGl knows how to use it
		VAO1.Bind();
		//std::cout << VAO;
		//render/draw primitives (e.g., points, lines, triangles) from vertex data.
		//(mode [GL_POINTS/ GL_LINES/ GL_TRIANGLES],first: Index of the first vertex to start rendering
		//from, count: Number of vertices to render.)
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT,0);

		//swap back buffer with front buffer
		glfwSwapBuffers(window);

		//Detects events such as mouse/keybard input events,should window be closed...main purpose 
		//of this is to make sure the app is responsive
		glfwPollEvents();
	}

	//TO keep things clean, delete all the objects that we created so far
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	//glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers(1, &VAO);
	//glDeleteBuffers(1, &EBO);
	//glDeleteProgram(shaderProgram);

	//Destroy the window we created
	glfwDestroyWindow(window);

	//Terminate/stop glfw
	glfwTerminate();

	return 0;
}