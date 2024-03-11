#include <iostream>
#include "Calculator.h"
float getRandomNum(const float& max, const float& min)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    // Define the range for the random number (integer and floating-point)
    std::uniform_real_distribution<float> dis(max, min);

    // Generate a random number
    float randomNumber = dis(gen);

    // If the random number is an integer or has one decimal place
    if( std::floor(randomNumber) == randomNumber || std::floor(randomNumber * 10) == ( randomNumber * 10 ) ) {
        //std::cout << "Random number: " << std::fixed << std::setprecision(1) << randomNumber << std::endl;
    }
    else {
        // Retry if not an integer or has one decimal place
        randomNumber = dis(gen);
        std::cout << "Random number: " << std::fixed << std::setprecision(1) << randomNumber << std::endl;
    }

    return randomNumber;
}

glm::vec3 calculateCubeSize(const float boundaryVertices[])
{
    glm::vec3 minCoords(boundaryVertices[ 0 ], boundaryVertices[ 1 ], boundaryVertices[ 2 ]);
    glm::vec3 maxCoords(boundaryVertices[ 0 ], boundaryVertices[ 1 ], boundaryVertices[ 2 ]);

    // Iterate through all vertices to find minimum and maximum coordinates
    for( int i = 3; i < 36; i += 3 ) {
        glm::vec3 vertex(boundaryVertices[ i ], boundaryVertices[ i + 1 ], boundaryVertices[ i + 2 ]);

        minCoords = glm::min(minCoords, vertex);
        maxCoords = glm::max(maxCoords, vertex);
    }

    // Calculate the size of the cube
    glm::vec3 cubeSize = maxCoords - minCoords;

    return cubeSize;
}

bool areEqual(float a, float b, float epsilon)
{
    return std::fabs(a - b) < epsilon;
}


