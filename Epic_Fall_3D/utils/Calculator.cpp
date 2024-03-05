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
        std::cout << "Random number: " << std::fixed << std::setprecision(1) << randomNumber << std::endl;
    }
    else {
        // Retry if not an integer or has one decimal place
        randomNumber = dis(gen);
        std::cout << "Random number: " << std::fixed << std::setprecision(1) << randomNumber << std::endl;
    }

    return randomNumber;
}
