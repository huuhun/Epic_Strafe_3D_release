#pragma once
#include <string>
#include <SDL_ttf.h>
class Text
{
public:
	bool loadFont(const std::string& path, int fontSize);
	void setTextColor(const unsigned char& red, const unsigned char& green,
					  const unsigned char& blue);
	void setText(const std::string& text);
	inline SDL_Surface* getTextSurface() { return m_TextSurface; }
	inline TTF_Font* getFont() { return m_Font; }

private:
	SDL_Color m_TextColor;
	SDL_Surface* m_TextSurface;
	TTF_Font* m_Font;
};