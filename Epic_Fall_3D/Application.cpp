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

int main(int argc, char* args[]) {

	if( !Window::initSDL() ) return -1;
	SDL_Window* window{ Window::createGLWindow("Epic Fall 3D", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WindowSettings::SCREEN_WIDTH, WindowSettings::SCREEN_HEIGHT, SDL_WINDOW_SHOWN) };
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
	SDL_Event event;
	while( true ) {
		while( SDL_PollEvent(&event) ) {
			if( event.type == SDL_QUIT )
				goto cleanup;
		}

		// create transformations

		glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f)); //This line translates (moves) the matrix by a specified vector (glm::vec3(0.5f, -0.5f, 0.0f)). In this case, it translates the matrix by 0.5 units along the x-axis and -0.5 units along the y-axis.
		const float rotationSpeed{ 0.002f };
		transform = glm::rotate(transform, (float)SDL_GetTicks() * rotationSpeed, glm::vec3(0.0f, 0.0f, 1.0f)); //This code is rotating the transformation matrix (transform) around the z-axis. The rotation angle is specified as (float)SDL_GetTicks(), which means it's using the current value of SDL ticks (time) as the angle of rotation.

		//Render here
		renderer.Clear();
		brickWallTexture.ActiveTexture(GL_TEXTURE0);
		brickWallTexture.Bind();
		faceTexture.ActiveTexture(GL_TEXTURE1);
		faceTexture.Bind();

		shader.Use();
		unsigned int transformLoc = glGetUniformLocation(shader.getID(), "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
		//renderer.DrawArrays();

		//Render container
		vao.Bind();
		renderer.DrawElements(sizeof(indices) / sizeof(indices[ 0 ])); // pass in the num of indices
		vao.Unbind();

		SDL_GL_SwapWindow(window);
	}

cleanup:
	Window::destroyWindow(context, window);

	return 0;
}
