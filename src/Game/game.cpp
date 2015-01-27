#define GLEW_STATIC
#include <GL/glew.h>
#include <SFML/Window.hpp>
#include "GLShader.hpp"
#include <iostream>

using namespace std;

int main()
{
	//a struct defining settings for the window
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;

	//create a new instance of sf::
	//sf::Style::Close makes sure the window is not resizable
	sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Close, settings);

	//glew helps set up your gl functions from the gpu drivers
	glewExperimental = GL_TRUE; //force glew to use modern OpenGL methods
	glewInit();

	//create and use a vertex array buffer, this will remember the links between vertex info and shader variables (which are set by glVertexArribPointer)
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//define the vertices
	float vertices[] = {
		 0.0f,  0.5f,
		 0.5f, -0.5f,
		-0.5f, -0.5f,
	};

	//vertex buffer object
	GLuint vbo;
	glGenBuffers(1, &vbo); //generate the vbo
	glBindBuffer(GL_ARRAY_BUFFER, vbo); //make the vbo the active array buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//load the shader programs
	GLuint program = LoadShader("src//Game//shader.vert", "src//Game//shader.frag");
	glUseProgram(program);

	//set up link between the vertex data and shader variables
	GLint posAttrib = glGetAttribLocation(program, "position"); //get the position variable from the vertex shader
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);  //make the link
	glEnableVertexAttribArray(posAttrib); //enable it!

	//event loop
	bool running = true;
	while(running){
		sf::Event windowEvent;
		while(window.pollEvent(windowEvent)){
			switch (windowEvent.type)
			{
				//case when the user attempts to close the window
				case sf::Event::Closed:
					running = false;
					break;
				default:
					break;
			}
		}

		// Clear the back buffer to black
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // Draw a triangle from the 3 vertices to the back buffer
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // Swap buffers
        window.display();
	}

	glDeleteProgram(program);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}