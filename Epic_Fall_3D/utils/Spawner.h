#pragma once

#include <array>
#include <vector>
#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include "Calculator.h"

#include "../Camera.h"
#include "../Model.h"
#include "../Shader.h"
#include "../Renderer.h"

std::vector<glm::vec3> spawnObstacles(const unsigned& posAmount);

std::vector<glm::vec3> spawnObstacles(const unsigned& posAmount, const bool& spinning);

std::array<glm::vec3, SPIN_OBSTACLES_NUM> spawnAxis(const unsigned& axisAmount);

glm::vec3 spawnBoundary(const float& x, const float& y, const float& z);

void spawnBoundariesVector(std::vector<glm::vec3>& leftBoundaryPos, std::vector<glm::vec3>& rightBoundaryPos, std::vector<glm::vec3>& topBoundaryPos, std::vector<glm::vec3>& bottomBoundaryPos);

void moveCameraHitbox(Camera& camera, Shader& shader);

void reallocateObstacles(std::vector<glm::vec3>& cubePos, const unsigned& verticesAmount, Camera& camera, Shader& shader, Renderer& renderer);

void reallocateSpinningObstacles(std::vector<glm::vec3>& cubePos, const unsigned& verticesAmount, Camera& camera, Shader& shader, Renderer& renderer/*, const glm::vec3& axis*/);

void reallocateBoundary(std::vector<glm::vec3>& cubePos, const unsigned& verticesAmount, Camera& camera, Shader& shader, Renderer& renderer);

glm::vec3  getLowestZValue(std::vector<glm::vec3>& cubePos);

glm::vec3 getHighestZValue(std::vector<glm::vec3>& cubePos);

void changeZValueIfItMatch(std::vector<glm::vec3>& vec3Vector, const glm::vec3& minZVec3, const float& newZValue);
