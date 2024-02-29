#pragma once

#include "VertexArray.h"

class VertexArray;

class Renderer
{
public:
	void setClearColor();

	//Call setClearColor first
	void Clear();

	void DrawArrays(const GLuint& elementsAmount) const;

	void DrawElements(const GLint& indicesAmount);

};