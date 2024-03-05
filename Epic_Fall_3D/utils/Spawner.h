#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Calculator.h"

#include "../Camera.h"
#include "../Model.h"
#include "../Shader.h"
#include "../Renderer.h"

std::vector<glm::vec3> spawnObstacles(const unsigned& posAmount);

void moveCameraHitbox(Camera& camera, Shader& shader);

void reallocateObstacles(std::vector<glm::vec3>& cubePos, const unsigned& verticesAmount, Camera& camera, Shader& shader, Renderer& renderer);
