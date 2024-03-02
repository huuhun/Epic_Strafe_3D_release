#include "Model.h"

Model::Model()
	:m_Model( glm::mat4(1.0f) )
{
}

void Model::setFixedModelRotation(const float& fixedDegree, const glm::vec3& axis) {
	
	//m_Model = glm::rotate(m_Model, glm::radians(fixedDegree), glm::vec3(0.5f, 1.0f, 0.0f));// converting -55 degrees to radians, model matrix is rotated around the x-axis by -55 degrees 
	m_Model = glm::rotate(m_Model, glm::radians(fixedDegree), axis);// converting -55 degrees to radians, model matrix is rotated around the x-axis by -55 degrees 
}

void Model::setSpinModelRotation(const float& rotationSpeed, const glm::vec3& axis) {

	//m_Model = glm::rotate(m_Model, glm::radians((float)SDL_GetTicks() * rotationSpeed), glm::vec3(0.5f, 1.0f, 0.0f));// converting -55 degrees to radians, model matrix is rotated around the x-axis by -55 degrees 
	m_Model = glm::rotate(m_Model, glm::radians(rotationSpeed), axis);// converting -55 degrees to radians, model matrix is rotated around the x-axis by -55 degrees 
}

void Model::setTranslation(const glm::vec3& cubePos) { 
	m_Model = glm::translate(m_Model, cubePos);
}
 
