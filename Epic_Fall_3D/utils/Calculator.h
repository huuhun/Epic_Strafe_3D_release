#pragma once
namespace cal {
	inline constexpr unsigned calVertexAmount(const unsigned& element_amount,
		const unsigned& elements_of_each_vertex)
	{
		return element_amount / elements_of_each_vertex;
	}
}