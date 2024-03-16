#pragma once
#include <string>
#include <ft2build.h>
#include FT_FREETYPE_H  
class Text
{
public:
	static void initFT();
	void createFTFace(const std::string& fontPath);
	void setPixelFontSize(const int& size);

private:
	static FT_Library m_FT;
	FT_Face m_Face;
};