#version 460 core

in vec2 fUV;

uniform sampler2D uTexture;

void main()
{
	gl_FragColor = texture(uTexture, fUV);
}