#version 460 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture sampler
uniform sampler2D brickWallTexture;
uniform sampler2D faceTexture;

void main()
{
	FragColor = mix(texture(brickWallTexture, TexCoord), texture(faceTexture, TexCoord), 0.6);
	//FragColor = texture(faceTexture, TexCoord);
}