#include "Spawner.h"

void moveCameraHitbox(Camera& camera, Shader& shader)
{
	Model playerCubeModel;
	playerCubeModel.setTranslation(/*playerCubePos **/ camera.Position);
	float angle{ 0.0f };
	playerCubeModel.setFixedModelRotation(angle, glm::vec3(1.0f, 0.3f, 0.5f));
	shader.setMat4("model", playerCubeModel.getModel());
	//renderer.DrawArrays(cal::calVertexAmount(sizeof(vertices) / sizeof(vertices[ 0 ]), 5));
}

void spawnObstacles(glm::vec3 cubePos[], const unsigned& cubePosAmount, const unsigned& verticesAmount ,Camera& camera, Shader& shader, Renderer& renderer)
{
	for( unsigned i = 0; i < ( cubePosAmount ); i++ )
	{
		if( camera.Position.z > cubePos[ i ].z - 5.0f )
		{
			Model cubeModel;
			cubeModel.setTranslation(cubePos[ i ]);
			float angle{ 20.0f * (float)i };
			cubeModel.setFixedModelRotation(angle, glm::vec3(1.0f, 0.3f, 0.5f));
			shader.setMat4("model", cubeModel.getModel());
			renderer.DrawArrays(verticesAmount);
		}
		else
		{
			cubePos[ i ].z += -40.0f;
		}
	}

}
