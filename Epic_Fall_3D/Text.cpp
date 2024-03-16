#include <iostream>
#include <glfw3.h>
#include "Text.h"

void Text::createFTFace(const std::string& fontPath)
{
	if( FT_New_Face(m_FT, fontPath.c_str(), 0, &m_Face) )
	{
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
	}
}

void Text::setPixelFontSize(const int& size) {
	FT_Set_Pixel_Sizes(m_Face, 0, size);
}


