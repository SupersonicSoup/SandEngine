#version 430 core
layout (location = 0) in vec4 vertex;

out vec2 uv;

uniform mat4 model;
uniform mat4 projection;

void main()
{
	vec4 worldPos = model * vec4(vertex.xy, 0.0, 1.0);
	gl_Position = projection * worldPos;
	uv = vertex.zw;
}