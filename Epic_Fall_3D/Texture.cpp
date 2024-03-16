#include <iostream>
#include <glad/glad.h>
#include <stb_image/stb_image.h>
#include "Texture.h"
Texture::Texture(const std::string& path)
	:m_ID(0)
{
	glGenTextures(1, &m_ID);
	glBindTexture(GL_TEXTURE_2D, m_ID); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR/*_MIPMAP_LINEAR*/);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	if( data )
	{
		//add this line to check if the image source have an alpha channel
		GLint internalFormat = ( static_cast<GLenum>( nrChannels == 4 ) ) ? GL_RGBA : GL_RGB;
		GLenum format = static_cast<GLenum>( nrChannels == 4 ? GL_RGBA : GL_RGB );
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;

	if( data )
		stbi_image_free(data);

	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(Text& text)
	:m_ID(0)
{
	glGenTextures(1, &m_ID);
	glBindTexture(GL_TEXTURE_2D, m_ID); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object



	// Set Texture Parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if( text.getTextSurface() )
	{
		int mode = text.getTextSurface()->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB;
		glTexImage2D(GL_TEXTURE_2D, 0, mode, text.getTextSurface()->w, text.getTextSurface()->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, text.getTextSurface()->pixels);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load text texture" << std::endl;

	// Check for OpenGL errors
	//GLenum error = glGetError();
	//if( error != GL_NO_ERROR ) {
	//	std::cerr << "Error creating texture: " << error << std::endl;
	//	// Optionally clean up and return 0
	//	glDeleteTextures(1, &m_ID);
	//}

	if( text.getTextSurface() != nullptr ) {
		std::cout << "I'M FREED ONCE ALREADY\n";
		SDL_FreeSurface(text.getTextSurface()); // Free the surface as we no longer need it
	}

	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_ID);
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_ID);
}

void Texture::ActiveTexture(const GLenum& TEXTURE_UNIT)
{
	glActiveTexture(TEXTURE_UNIT);
	Bind();
}