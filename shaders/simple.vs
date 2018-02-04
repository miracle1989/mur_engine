#version 330

layout(location = 0) in vec3 Pos;

uniform mat4 gMVP;

void main()
{
	gl_Position = gMVP * vec4(Pos, 1.0);
}