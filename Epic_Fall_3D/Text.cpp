#include <iostream>
#include <SDL_ttf.h>
#include <glfw3.h>
#include "Text.h"

bool Text::loadFont(const std::string& path, int fontSize)
{
    m_Font = TTF_OpenFont(path.c_str(), fontSize);
    if( !m_Font ) {
        TTF_Quit();
        glfwTerminate();
        return -1;
    }
}

void Text::setTextColor(const unsigned char& red, const unsigned char& green,
                        const unsigned char& blue, const unsigned char& alpha)
{
    m_TextColor = { red, green, blue, alpha };
}

void Text::setText(const std::string& text)
{
    m_TextSurface = TTF_RenderText_Solid(m_Font, "Hello, GLFW and OpenGL!", m_TextColor);
}

