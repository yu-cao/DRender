#version 330

uniform mat4 in_MVP;

in vec4 in_Position;
in vec4 in_Color;

out vec4 ex_Color;

void main()
{
	gl_Position = in_MVP * in_Position;
	ex_Color = in_Color;
}