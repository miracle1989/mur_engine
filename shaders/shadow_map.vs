#version 330

layout(location = 0) in vec3 Position;
layout(location = 1) in vec2 TexCoord;

uniform mat4 gMVP;
out vec2 TexCoordOut;

void main()
{
	gl_Position = gMVP * vec4(Position, 1);
	TexCoordOut = TexCoord;
} 