#pragma once
#include <random>
#include <iomanip>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>

inline constexpr unsigned calVertexAmount(const unsigned& element_amount,
	const unsigned& elements_of_each_vertex)
{
	return element_amount / elements_of_each_vertex;
}

float getRandomNum(const float& min, const float& max);

glm::vec3 calculateCubeSize(const float boundaryVertices[]);

bool areEqual(float a, float b, float epsilon = 1e-5);



