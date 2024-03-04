#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Calculator.h"

#include "../Camera.h"
#include "../Model.h"
#include "../Shader.h"
#include "../Renderer.h"

void moveCameraHitbox(Camera& camera, Shader& shader);

void spawnObstacles(glm::vec3 cubePos[], const unsigned& cubePosAmount, const unsigned& verticesAmount, Camera& camera, Shader& shader, Renderer& renderer);
