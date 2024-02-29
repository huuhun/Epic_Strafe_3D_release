#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SDL.h>
#include <glad/glad.h>
#include <stb_image/stb_image.h>

#include "Window.h"
#include "Settings.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Debugger.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "Transform.h"

int main(int argc, char* args[]) {

	if( !Window::initSDL() ) return -1;
	SDL_Window* window{ Window::createGLWindow("Epic Fall 3D", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WindowSettings::SCR_WIDTH, WindowSettings::SCR_HEIGHT, SDL_WINDOW_SHOWN) };
	SDL_GLContext context{ Window::createGLContext(window) };
	Window::loadGLFunctionPointers();
	Window::setGLVersion(4);
	Window::getGLVersion();


	float vertices[] = {
		// positions          // colors           // texture coords
	   0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
	   0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
	  -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
	  -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};

	unsigned indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	VertexArray vao;
	VertexBuffer vbo;
	IndexBuffer ebo;

	vao.Bind();

	vbo.Bind();
	vbo.BufferData(vertices, sizeof(vertices) / sizeof(vertices[ 0 ]));

	// position attribute
	VertexArray::LinkAttrib(0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	// color attribute
	VertexArray::LinkAttrib(1, 3, GL_FLOAT, 8 * sizeof(float), (void*)( 3 * sizeof(float) ));
	// texture coord attribute
	VertexArray::LinkAttrib(2, 2, GL_FLOAT, 8 * sizeof(float), (void*)( 6 * sizeof(float) ));

	ebo.Bind();
	ebo.BufferData(indices, sizeof(indices) / sizeof(indices[ 0 ]));

	vbo.Unbind();
	vao.Unbind();

	enableGLDebugContext();

	Shader shader("res/shaders/shader460.vert", "res/shaders/shader460.frag");

	Texture brickWallTexture("res/textures/brick-wall.png");
	Texture faceTexture("res/textures/face.png");

	shader.Use();

	shader.setInt("brickWallTexture", 0);
	shader.setInt("faceTexture", 1);

	Renderer renderer;
	renderer.setClearColor();
	SDL_Event e;
	Uint32 frameStart;
	while( true ) {
		frameStart = SDL_GetTicks();

		while( SDL_PollEvent(&e) ) {
			if( e.type == SDL_QUIT )
				goto cleanup;
		}
		shader.Use();
		// create transformations
		//Transform transform(0.001);
		glm::mat4 model      = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		glm::mat4 view       = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0, 0.0f, 0.0f));// converting -55 degrees to radians, model matrix is rotated around the x-axis by -55 degrees 
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); //The view matrix is translated along the z-axis by -3 units using 
		projection = glm::perspective(glm::radians(45.0f), (float)WindowSettings::SCR_WIDTH / (float)WindowSettings::SCR_HEIGHT, 0.1f, 100.0f); //// Parameters: Field of view, aspect ratio, near clipping plane, far clipping plane
		// retrieve the matrix uniform locations
		unsigned int modelLoc = glGetUniformLocation(shader.getID(), "model");
		unsigned int viewLoc = glGetUniformLocation(shader.getID(), "view");
		// pass them to the shaders (3 different ways)
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[ 0 ][ 0 ]);
		// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
		shader.setMat4("projection", projection);

		//Render here
		renderer.Clear();
		brickWallTexture.ActiveTexture(GL_TEXTURE0);
		brickWallTexture.Bind();
		faceTexture.ActiveTexture(GL_TEXTURE1);
		faceTexture.Bind();

		// get matrix's uniform location and set matrix
		//shader.Use();
		//unsigned int transformLoc = glGetUniformLocation(shader.getID(), "transform");
		//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
		//shader.setMat4("transform", transform.getTransform());
		//renderer.DrawArrays();

		//Render container
		vao.Bind();
		renderer.DrawElements(sizeof(indices) / sizeof(indices[ 0 ])); // pass in the num of indices
		vao.Unbind();

		Window::capFramerate(frameStart, WindowSettings::MAX_FPS);

		SDL_GL_SwapWindow(window);
	}

cleanup:
	Window::destroyWindow(context, window);

	return 0;
}
