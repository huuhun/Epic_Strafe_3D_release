#pragma once
#include <string>
class Text
{
public:
	Text();
	void loadFont();
	void setFontSize();
private:
	static std::string m_FontPath;
};
