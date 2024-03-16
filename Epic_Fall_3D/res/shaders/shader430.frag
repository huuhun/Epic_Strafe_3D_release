#version 430 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

flat in int RenderType;  // Uniform indicating the type of cube to render

// texture sampler
uniform sampler2D brickWallTexture;
uniform sampler2D faceTexture;
uniform sampler2D boundaryTexture;
uniform sampler2D testTextTexture;

void main()
{
    if (RenderType == 1)
    {
        FragColor = texture(boundaryTexture, TexCoord);
    }
    else if (RenderType == 0)
    {
	    //FragColor = mix(texture(brickWallTexture, TexCoord), texture(testTextTexture, TexCoord), 0.4);
	    //FragColor = mix( mix(texture(brickWallTexture, TexCoord), texture(faceTexture, TexCoord), 0.4), texture(testTextTexture, TexCoord), 0.5 );
        FragColor = texture(testTextTexture, TexCoord);
    }
}