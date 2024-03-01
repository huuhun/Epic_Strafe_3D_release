#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//#include "Shader.h"
//#include "Renderer.h"
//
//class Shader;
//class Renderer;

class Model
{
public:
	Model();

	void setFixedModelRotation(const float& fixedDegree, const glm::vec3& axis);

	void setSpinModelRotation(const float& rotationSpeed, const glm::vec3& axis);
	//translate mean move an object/model to different place
	void setTranslation(const glm::vec3& cubePos);

	inline void resetModel() { m_Model = glm::mat4(1.0f); }

	inline glm::mat4 getModel() { return m_Model; };

private:
	glm::mat4 m_Model;
};
