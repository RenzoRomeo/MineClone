#version 460 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aUV;
layout(location = 2) in vec2 aAtlasCoords;

uniform int uAtlasW;
uniform int uAtlasH;
uniform int uAtlasSpriteSize;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

out vec2 fUV;

void main()
{
	float x = (aAtlasCoords.x + aUV.x) * uAtlasSpriteSize / uAtlasW;
	float y = (aAtlasCoords.y + aUV.y) * uAtlasSpriteSize / uAtlasH;

	fUV = vec2(x, y);
	gl_Position = uProjection * uView * (uModel * vec4(aPos, 1.0));
}