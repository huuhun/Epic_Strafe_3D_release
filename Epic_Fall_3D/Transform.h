#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Transform
{
public:
	Transform();
	//void setSpinner(const float& rotationSpeed);

	void setProjection();
	void setView();
	void setModel(const float& rotationSpeed = 0.0f);

	void resetModel() { m_Model = glm::mat4(0.1f); };
	void resetView() { m_View = glm::mat4(0.1f); };
	void resetProjection() { m_Projection = glm::mat4(0.1f); };

	//inline glm::mat4 getTransform() const { return m_Transform; }
	inline glm::mat4 getModel() const { return m_Model; }
	inline glm::mat4 getView() const { return m_View; }
	inline glm::mat4 getProjection() const { return m_Projection; }
private:
	glm::mat4 m_Transform, m_Model, m_Projection, m_View;
};
