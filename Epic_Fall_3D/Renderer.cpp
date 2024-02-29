#include <glad/glad.h>

#include "Renderer.h"

void Renderer::setClearColor()
{
	// Set clear color to light green
	glClearColor(0.5f, 1.0f, 0.5f, 1.0f);
}

void Renderer::Clear()
{
	//glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

}

void Renderer::DrawArrays(const GLuint& elementsAmount) const {

	//shader.Bind(); //giving instructions to GPU as to whatever we're trying to draw what we draw

	//array that contains all the actual data, so the program or the shader says what to do with
	//the data, and this vertex array is the data we going to do stuff with,
	//this includes vertex buffer and index buffer. 
	//Vertex buffer contains all the vertex data and incluing the positions of each kind of point that we trying to render:
	//texture coords (now we only use that), vertex colors, normals, tangents...  
	//VAO.Bind();

	//index buffer contains the indices into the vertex buffer so that we can choose which vertices we actually want to render
	//and how to kind of assemble together
	//ib.Bind();

	//glDrawElements just says hey u know using that index buffer access the vertex buffer and call the shader program
	//on all those vertices indivially to actually get it to draw and rasterize our object onto the screens
	glDrawArrays(GL_TRIANGLES, 0, elementsAmount);
}

void Renderer::DrawElements(const GLint& indicesAmount) {
	glDrawElements(GL_TRIANGLES, indicesAmount, GL_UNSIGNED_INT, nullptr);
}