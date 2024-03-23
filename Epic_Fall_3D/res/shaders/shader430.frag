#version 430 core

out vec4 FragColor;

//in vec3 textColor;
in vec2 TexCoord;

flat in int RenderType;  // Uniform indicating the type of cube to render

// texture sampler
uniform sampler2D brickWallTexture;
uniform sampler2D faceTexture;
uniform sampler2D boundaryTexture;
uniform sampler2D enterTextBackgroundTexture;
uniform sampler2D gameOverTextBackgroundTexture;

uniform vec3 textColor;

void main()
{
    if (RenderType == 1)
    {
        FragColor = texture(boundaryTexture, TexCoord);
    }
    else if (RenderType == 0)
    {
	    FragColor = mix( texture(brickWallTexture, TexCoord), texture(faceTexture, TexCoord), 0.4 );
	    //FragColor = mix( mix(texture(brickWallTexture, TexCoord), texture(faceTexture, TexCoord), 0.4), texture(testTextTexture, TexCoord), 0.5 );
        //FragColor = texture(testTextTexture, TexCoord);
    }
    else if(RenderType == 2){
         FragColor = texture(enterTextBackgroundTexture, TexCoord);
    }
    else if(RenderType == 3){
         FragColor = texture(gameOverTextBackgroundTexture, TexCoord);
    }
}