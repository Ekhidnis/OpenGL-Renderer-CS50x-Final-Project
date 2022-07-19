#version 460

layout(location = 0) in vec3 pos;

out vec4 vertexColor;

uniform mat4 model;
uniform mat4 projection;

void main()
{
	gl_Position = projection * model * vec4(pos, 1.f);
	vertexColor = vec4(clamp(pos, 0.f, 1.f), 1.f);
}