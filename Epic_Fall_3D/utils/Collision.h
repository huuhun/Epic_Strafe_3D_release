#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

bool checkCollision(const glm::vec3& pos1, const glm::vec3& pos2);

bool isCollidingWithPlane(const float cubeVertices[], int numVertices, float planeConstant);
