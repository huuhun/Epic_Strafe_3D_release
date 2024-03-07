#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

bool checkCollision(const glm::vec3& pos1, const glm::vec3& pos2);

bool checkBoundaryCollision(const glm::vec3& cameraPosition, const float boundaryVertices[]);

bool isCameraColliding(const glm::vec3& cameraPosition, const std::vector<glm::vec3>& cubePositions, const glm::vec3& cubeSize);

