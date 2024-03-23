#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
//layout (location = 2) in vec4 vertex; // <vec2 pos, vec2 tex>

out vec2 TexCoord;

flat out int RenderType;  // Uniform indicating the type of cube to render

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// Flag to determine which cube to render
uniform int renderFlag;  // Set to 0 for the brick wall cube, 1 for the boundary cube
void main()
{
	RenderType = renderFlag;
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	TexCoord = aTexCoord;
	//if(renderTextFlag == 0){
	//}
	//else if(renderTextFlag == 1){
	//gl_Position = projection * view * model * vec4(vertex.xy, 0.0, 1.0);
	//TexCoord = vertex.zw;
	//}
	//gl_Position = projection * view * model * vec4(aPos, 1.0);
	//TexCoord = aTexCoord;

}