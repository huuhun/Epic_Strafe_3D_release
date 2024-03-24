#pragma once

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


void clearEntity(std::vector<glm::vec3>& pos);

void spawnNewEntities(std::vector<glm::vec3>& cubePos, std::vector<glm::vec3>& spinCubePos, std::vector<glm::vec3>& spinCubeAxes, std::vector<glm::vec3>& leftBoundaryPos, std::vector<glm::vec3>& rightBoundaryPos, std::vector<glm::vec3>& topBoundaryPos, std::vector<glm::vec3>& bottomBoundaryPos);

void restart(std::vector<glm::vec3>& cubePos, std::vector<glm::vec3>& spinCubePos, std::vector<glm::vec3>& spinCubeAxes, std::vector<glm::vec3>& leftBoundaryPos, std::vector<glm::vec3>& rightBoundaryPos, std::vector<glm::vec3>& topBoundaryPos, std::vector<glm::vec3>& bottomBoundaryPos);
