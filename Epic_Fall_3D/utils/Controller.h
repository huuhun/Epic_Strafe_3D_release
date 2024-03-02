#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glfw3.h>

#include "Settings.h"

void processInput(GLFWwindow* window, float& deltaTime, glm::vec3& cameraPos,
	glm::vec3& cameraFront, glm::vec3& cameraUp);