#version 330 core

in vec3 vertexColor;
in vec2 vertexUV;

uniform sampler2D outTexture;

out vec4 FragColor;

void main() {
	FragColor = texture(outTexture, vertexUV) * vec4(vertexColor, 1.0);
}