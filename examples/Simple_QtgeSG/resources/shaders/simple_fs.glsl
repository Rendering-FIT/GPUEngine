#version 430

layout(location=0)out vec4 fragColor;

uniform layout(binding = 0) sampler2D diffTex;

uniform vec4 color;

in vec2 uv;

void main()
{
   fragColor = texture(diffTex,uv) * color;
}