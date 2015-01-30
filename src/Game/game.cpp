#define GLEW_STATIC
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "GLShader.hpp"
#include <iostream>
#include <time.h>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

int main()
{
    //tell sdl to load the video module

    SDL_Init(SDL_INIT_VIDEO);

    //tell sdl which gl profile touse
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); //use openg gl core profile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3); //use version 3.2
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    //create window and context
    SDL_Window* window = SDL_CreateWindow("OpenGL", 100, 100, 800, 600, SDL_WINDOW_OPENGL); //last param: window for opengl
    SDL_GLContext context = SDL_GL_CreateContext(window);

    //glew helps set up your gl functions from the gpu drivers
	glewExperimental = GL_TRUE; //force glew to use modern OpenGL methods
	glewInit();

	//create and use a vertex array buffer, this will remember the links between vertex info and shader variables (which are set by glVertexArribPointer)
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//define the vertices
	GLfloat vertices[] = {
	//   X		Y 	   Z     R     G     B     U     V		
	    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	     0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	     0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	     0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

	    -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	     0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	    -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	    -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

	    -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	    -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	    -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

	     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	     0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	     0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	     0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	     0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

	    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	     0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	     0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	     0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	    -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

	    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	     0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	    -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

	    //floor
	    -1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	     1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	     1.0f,  1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	     1.0f,  1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	    -1.0f,  1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	    -1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f
	};

	//vertex buffer object
	GLuint vbo;
	glGenBuffers(1, &vbo); //generate the vbo
	glBindBuffer(GL_ARRAY_BUFFER, vbo); //make the vbo the active array buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//create and use a element buffer
	GLuint ebo;
	glGenBuffers(1, &ebo);

	GLuint elements[] = {
	    0, 1, 2,
	    2, 3, 0
	};

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	//load the shader programs
	GLuint program = LoadShader("src//Game//shader.vert", "src//Game//shader.frag");
	glUseProgram(program);

	//set up link between the vertex data and shader variables
	GLint posAttrib = glGetAttribLocation(program, "position"); //get the position variable from the vertex shader
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), 0);  //make the link
	glEnableVertexAttribArray(posAttrib); //enable it

	//now for color
	GLint colAttrib = glGetAttribLocation(program, "color");
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void *)(3*sizeof(float)));
	glEnableVertexAttribArray(colAttrib);

	//for the tex coords
	GLint texAttrib = glGetAttribLocation(program, "texcoord");
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void *)(6*sizeof(float)));
	glEnableVertexAttribArray(texAttrib);

	//create texture object and bind to GL_TEXTURE_2D
	GLuint tex[2];
	glGenTextures(2, tex);

	//activate texture 0, bind to that texture, load the image to that texture, set the uniform texKitten to that texture and set some proterties for texture 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex[0]);
	SDL_Surface *surface1 = SDL_LoadBMP("src//Game//img.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surface1->w, surface1->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface1->pixels);
	GLint texKittenUniform = glGetUniformLocation(program, "texKitten");
	glUniform1i(texKittenUniform, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //activate texture 1, bind to that texture, load the image to that texture, set the uniform texPuppy to that texture and set some proterties for texture 1
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, tex[1]);
	SDL_Surface *surface2 = SDL_LoadBMP("src//Game//img2.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surface2->w, surface2->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface2->pixels);
	GLint texPupptUniform = glGetUniformLocation(program, "texPuppy");
	glUniform1i(texPupptUniform, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
	//get the uniform variable
	GLint uniModel = glGetUniformLocation(program, "model");
	GLint uniView = glGetUniformLocation(program, "view");
	GLint uniProj = glGetUniformLocation(program, "proj");
	GLint uniOverCol = glGetUniformLocation(program, "overrideColor");
	float start = clock();

	//set the view and projection matrices
	glm::mat4 view = glm::lookAt(
	    glm::vec3(2.0f, 2.0f, 1.2f),
	    glm::vec3(0.0f, 0.0f, 0.0f),
	    glm::vec3(0.0f, 0.0f, 1.0f)
	);
	glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

	glm::mat4 proj = glm::perspective(45.0f, 800.0f / 600.0f, 1.0f, 10.0f);
	glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

	glEnable(GL_DEPTH_TEST);

	//event loop
	SDL_Event windowEvent;
	while(true){
		if (SDL_PollEvent(&windowEvent)){
            if (windowEvent.type == SDL_QUIT) break;
        }

		// Clear the back buffer to black
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        float seconds = ((float)clock() - start)/CLOCKS_PER_SEC;

        glm::mat4 model;
        model = glm::rotate(model, seconds * 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));

        glDepthMask(GL_TRUE);
        glClear(GL_DEPTH_BUFFER_BIT);

        //draw the cube
        glDrawArrays(GL_TRIANGLES, 0, 36);

		// Draw floor
		glEnable(GL_STENCIL_TEST);
		glStencilFunc(GL_ALWAYS, 1, 0xFF); // Set any stencil to 1
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		glStencilMask(0xFF); // Write to stencil buffer
		glDepthMask(GL_FALSE); // Don't write to depth buffer
		glClear(GL_STENCIL_BUFFER_BIT); // Clear stencil buffer (0 by default)

		glDrawArrays(GL_TRIANGLES, 36, 6);

		// Draw cube reflection
		glStencilFunc(GL_EQUAL, 1, 0xFF); // Pass test if stencil value is 1
		glStencilMask(0x00); // Don't write anything to stencil buffer
		glDepthMask(GL_TRUE); // Write to depth buffer

		model = glm::scale(glm::translate(model, glm::vec3(0, 0, -1)), glm::vec3(1, 1, -1));
		glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));

		glUniform3f(uniOverCol, 0.3f, 0.3f, 0.3f);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glUniform3f(uniOverCol, 1.0f, 1.0f, 1.0f);

		glDisable(GL_STENCIL_TEST);

        SDL_GL_SwapWindow(window);
	}

	glDeleteTextures(1, tex);
	glDeleteProgram(program);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    SDL_GL_DeleteContext(context);
    //unload modules
    SDL_Quit();

    return 0;
}