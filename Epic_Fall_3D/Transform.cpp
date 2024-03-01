#include <SDL.h>
#include <Settings.h>

#include "Transform.h"

Transform::Transform()
	: m_Projection{ glm::mat4(1.0f) }, m_View{ glm::mat4(1.0f) }// make sure to initialize matrix to identity matrix first 
{
}

//void Transform::setSpinner(const float& rotationSpeed) {
//	// create transformations
//	m_Transform = glm::translate(m_Transform, glm::vec3(0.5f, -0.5f, 0.0f)); //This line translates (moves) the matrix by a specified vector (glm::vec3(0.5f, -0.5f, 0.0f)). In this case, it translates the matrix by 0.5 units along the x-axis and -0.5 units along the y-axis.
//	m_Transform = glm::rotate(m_Transform, (float)SDL_GetTicks() * rotationSpeed, glm::vec3(0.0f, 0.0f, 1.0f)); //This code is rotating the transformation matrix (transform) around the z-axis. The rotation angle is specified as (float)SDL_GetTicks(), which means it's using the current value of SDL ticks (time) as the angle of rotation.
//}


void Transform::setProjection() {
	// create transformations
	m_Projection = glm::perspective(glm::radians(45.0f), (float)WindowSettings::SCR_WIDTH / (float)WindowSettings::SCR_HEIGHT, 0.1f, 100.0f); //// Parameters: Field of view, aspect ratio, near clipping plane, far clipping plane
}

void Transform::setView() {
	// create transformations
	m_View = glm::translate(m_View, glm::vec3(0.0f, 0.0f, -3.0f)); //The view matrix is translated along the z-axis by -3 units using 
}

//void Transform::setSpinModel(const float& rotationSpeed) {
//	//m_Model = glm::rotate(m_Model, glm::radians(-55.0f), glm::vec3(1.0, 0.0f, 0.0f));// converting -55 degrees to radians, model matrix is rotated around the x-axis by -55 degrees 
//	m_Model = glm::rotate(m_Model, (float)SDL_GetTicks() * rotationSpeed, glm::vec3(0.5f, 1.0f, 0.0f));// converting -55 degrees to radians, model matrix is rotated around the x-axis by -55 degrees 
//
//}

//void Transform::setFixedModel(const float& fixedDegree) {
//	//m_Model = glm::rotate(m_Model, glm::radians(-55.0f), glm::vec3(1.0, 0.0f, 0.0f));// converting -55 degrees to radians, model matrix is rotated around the x-axis by -55 degrees 
//	m_Model = glm::rotate(m_Model, fixedDegree, glm::vec3(0.5f, 1.0f, 0.0f));// converting -55 degrees to radians, model matrix is rotated around the x-axis by -55 degrees 
//}

//void Transform::makeModel(){
//	m_Model = glm::mat4(1.0f);
//}

//void Transform::sendModelToShader(Shader& shader) {
//	shader.setMat4("model", m_Model);
//}


//void Transform::drawFixedModels(const glm::vec3* cubePos, const int& elementAmount, Shader& shader, Renderer& renderer, const int& verticesAmount) {
//	for( unsigned int i = 0; i < elementAmount; i++ )
//	{
//		// calculate the model matrix for each object and pass it to shader before drawing
//		//makeModel();
//		//m_Model = glm::translate(m_Model, cubePos[ i ]);
//		//float angle = 20.0f * i;
//		//m_Model = glm::rotate(m_Model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//		
//		sendModelToShader(shader);
//
//		renderer.DrawArrays(verticesAmount);
//	}
//}
