#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Renderer.h"

class Shader;
class Renderer;

class Transform
{
public:
	Transform();

	void setProjection();
	void setProjection(float& fov, const float& aspectRatio, const float& nearClippingPlane, const float& farClippingPlane);

	void setView();
	void setCameraView(const glm::mat4& viewMatrix);

	void resetView() { m_View = glm::mat4(0.1f); };
	void resetProjection() { m_Projection = glm::mat4(0.1f); };

	inline glm::mat4 getView() const { return m_View; }
	inline glm::mat4 getProjection() const { return m_Projection; }
private:
	glm::mat4 m_Projection, m_View;
};
