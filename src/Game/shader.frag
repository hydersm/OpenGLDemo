#version 150

in vec3 Color;
in vec2 Texcoord;

uniform vec3 triangleColor;

uniform sampler2D texKitten;
uniform sampler2D texPuppy;

out vec4 outColor;

void main()
{
	vec4 colKitten = texture(texKitten, Texcoord);
	vec4 colPuppy = texture(texPuppy, Texcoord);

	vec4 texColor = mix(colKitten, colPuppy, 0.5);

	outColor = vec4(Color, 1.0) * texColor;
}