#include "Utils.h"
#include "Settings.h"
#include "Spawner.h"

inline void clearEntity(std::vector<glm::vec3>& pos) {
	pos.clear();
}

void spawnNewEntities(std::vector<glm::vec3>& cubePos, std::vector<glm::vec3>& spinCubePos,
					  std::vector<glm::vec3>& spinCubeAxes, std::vector<glm::vec3>& leftBoundaryPos,
					  std::vector<glm::vec3>& rightBoundaryPos, std::vector<glm::vec3>& topBoundaryPos,
					  std::vector<glm::vec3>& bottomBoundaryPos)
{

	std::thread spawnObstaclesPosThread([&]() {
		cubePos = spawnObstacles(OBSTACLES_NUM);
										});

	std::thread spawnSpinObstaclesPosThread([&]() {
		spinCubePos = spawnObstacles(SPIN_OBSTACLES_NUM, true);
											});

	std::thread spawnSpinObstaclesAxesThread([&]() {
		spinCubeAxes = spawnAxes(SPIN_OBSTACLES_NUM);
											 });

	std::thread spawnBoundariesPosThread([&]() {
		spawnBoundariesVector(leftBoundaryPos, rightBoundaryPos, topBoundaryPos, bottomBoundaryPos);
										 });

	spawnObstaclesPosThread.join();
	spawnSpinObstaclesPosThread.join();
	spawnSpinObstaclesAxesThread.join();
	spawnBoundariesPosThread.join();
}

void restart(std::vector<glm::vec3>& cubePos, std::vector<glm::vec3>& spinCubePos,
			 std::vector<glm::vec3>& spinCubeAxes, std::vector<glm::vec3>& leftBoundaryPos,
			 std::vector<glm::vec3>& rightBoundaryPos, std::vector<glm::vec3>& topBoundaryPos,
			 std::vector<glm::vec3>& bottomBoundaryPos)
{
	clearEntity(cubePos);
	clearEntity(spinCubePos);
	clearEntity(spinCubeAxes);
	clearEntity(leftBoundaryPos);
	clearEntity(rightBoundaryPos);
	clearEntity(topBoundaryPos);
	clearEntity(bottomBoundaryPos);
}
