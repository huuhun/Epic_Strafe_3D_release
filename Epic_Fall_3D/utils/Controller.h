#pragma once
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Settings.h"
#include "../Camera.h"
#include "States.h"
#include "../Music.h"


void processInput(GLFWwindow* window, float& deltaTime, Camera& camera, PlayState& state);

void processInput(GLFWwindow* window, float& deltaTime, Camera& camera, PlayState& state, bool& spawnNewEntitiesFlag);
