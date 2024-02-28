#version 460 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture sampler
uniform sampler2D brickWallBlockTexture;

void main()
{
	FragColor = texture(brickWallBlockTexture, TexCoord);
}