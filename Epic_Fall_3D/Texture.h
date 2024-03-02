#pragma once
#include <string>
class Texture
{
private:
	unsigned int m_ID;
	/*std::string m_FilePath;
	unsigned char* m_LocalBuffer;*/
	//int m_Width, m_Height, m_BPP; //Bytes per pixel
public:
	Texture(const std::string& path);
	~Texture();

	void Bind();

	void ActiveTexture(const GLenum& TEXTURE_UNIT);

	/*void Bind(unsigned int slot = 0) const;
	void Unbind() const;*/

	/*inline int getWidth() const { return m_Width; }
	inline int getHeight() const { return m_Height; }*/
	inline unsigned int getID() const { return m_ID; }
};