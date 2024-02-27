#pragma once

#include "VertexArray.h"

class VertexArray;

class Renderer
{
public:
	void setClearColor();

	//Call setClearColor first
	void Clear();

	void Draw(const VertexArray& VAO) const;

};