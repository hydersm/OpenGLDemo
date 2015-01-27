#define GLEW_STATIC
#include <GL/glew.h>
#include <SFML/Window.hpp>

int main()
{
	//a struct defining settings for the window
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 2;

	//create a new instance of sf::
	//sf::Style::Close makes sure the window is not resizable
	sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Close, settings);

	//glew helps set up your gl functions from the gpu drivers
	glewExperimental = GL_TRUE; //force glew to use modern OpenGL methods
	glewInit();

	//test if glewInit() was succesfull
	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	printf("%u\n", vertexBuffer);

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
	}
}