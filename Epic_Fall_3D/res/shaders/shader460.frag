#version 460 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture sampler
//uniform sampler2D brickWallBlockTexture;
uniform sampler2D faceTexture;

void main()
{
	//FragColor = mix(texture(brickWallBlockTexture, TexCoord), texture(faceTexture, TexCoord), 0.2);
	FragColor = texture(faceTexture, TexCoord);
}