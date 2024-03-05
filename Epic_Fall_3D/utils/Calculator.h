#pragma once
#include <random>
#include <iomanip>

inline constexpr unsigned calVertexAmount(const unsigned& element_amount,
	const unsigned& elements_of_each_vertex)
{
	return element_amount / elements_of_each_vertex;
}

float getRandomNum(const float& min, const float& max);


