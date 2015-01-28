#define GLEW_STATIC
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "GLShader.hpp"
#include <iostream>
#include <time.h>
#include <math.h>

using namespace std;

int main()
{
    //tell sdl to load the video module
    SDL_Init(SDL_INIT_VIDEO);

    //tell sdl which gl profile touse
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); //use openg gl core profile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3); //use version 3.2
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    //create window and context
    SDL_Window* window = SDL_CreateWindow("OpenGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL); //last param: window for opengl
    SDL_GLContext context = SDL_GL_CreateContext(window);

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
	glEnableVertexAttribArray(posAttrib); //enable it

	//get the uniform variable
	GLint uniColor = glGetUniformLocation(program, "triangleColor");

	//event loop
	SDL_Event windowEvent;
	while(true){
		if (SDL_PollEvent(&windowEvent)){
            if (windowEvent.type == SDL_QUIT) break;
        }

		// Clear the back buffer to black
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        float seconds = clock()/CLOCKS_PER_SEC;
        float redComponent = sin(seconds)/2 + 0.5;

        //set the uniform variable
        glUniform3f(uniColor, redComponent, 0.0f, 0.0f);

        // Draw a triangle from the 3 vertices to the back buffer
        glDrawArrays(GL_TRIANGLES, 0, 3);

        SDL_GL_SwapWindow(window);
	}

	glDeleteProgram(program);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    SDL_GL_DeleteContext(context);
    //unload modules
    SDL_Quit();

    return 0;
}