#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Transform
{
public:
	Transform(const float& rotationSpeed);
	inline glm::mat4 getTransform() const { return m_Transform; }
private:
	glm::mat4 m_Transform;
};
