#include <SDL.h>

#include "Transform.h"

Transform::Transform(const float& rotationSpeed)
	:m_Transform{ glm::mat4(1.0f) }// make sure to initialize matrix to identity matrix first 
{
	// create transformations
	m_Transform = glm::translate(m_Transform, glm::vec3(0.5f, -0.5f, 0.0f)); //This line translates (moves) the matrix by a specified vector (glm::vec3(0.5f, -0.5f, 0.0f)). In this case, it translates the matrix by 0.5 units along the x-axis and -0.5 units along the y-axis.
	m_Transform = glm::rotate(m_Transform, (float)SDL_GetTicks() * rotationSpeed, glm::vec3(0.0f, 0.0f, 1.0f)); //This code is rotating the transformation matrix (transform) around the z-axis. The rotation angle is specified as (float)SDL_GetTicks(), which means it's using the current value of SDL ticks (time) as the angle of rotation.
}
