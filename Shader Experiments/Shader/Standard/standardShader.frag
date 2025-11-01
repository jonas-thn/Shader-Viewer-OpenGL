#version 330 core

in vec2 TexCoords;
in vec3 Normals;
in vec3 FragPos;

uniform vec3 cameraPos;

out vec4 FragColor;

void main()
{
	vec3 baseColor = vec3(1.0);

	FragColor = vec4(baseColor, 1.0);
}
