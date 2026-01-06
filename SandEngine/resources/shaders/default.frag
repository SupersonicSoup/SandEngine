#version 430 core
out vec4 FragColor;
in vec2 uv;

uniform sampler2D img;

void main()
{
	vec3 col = texture(img, uv).rgb;
	FragColor = vec4(col, 1.0);
}