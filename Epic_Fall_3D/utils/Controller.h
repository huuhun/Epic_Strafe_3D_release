#pragma once
#include <SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Settings.h"

bool processInput(SDL_Event& e, float& deltaTime, glm::vec3& cameraPos,
	glm::vec3& cameraFront, glm::vec3& cameraUp);