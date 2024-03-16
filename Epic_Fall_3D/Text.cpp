#include <iostream>
#include <glfw3.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "Text.h"

FT_Library Text::m_FT;

void Text::initFT() 
{
	if( FT_Init_FreeType(&m_FT) )
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
}

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

//void Text::loadCharGlyph(const unsigned char& c) {
//	if( FT_Load_Char(face, c, FT_LOAD_RENDER) )
//	{
//		std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
//		continue;
//	}
//}


