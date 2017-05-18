#version 420

layout(location = 0) in vec2 Position;
layout(location = 1) in vec2 TexCoords;

out vec2 TexCoords1;

uniform float ScreenWidth;
uniform float ScreenHeight;
uniform float Width;
uniform float Height;
uniform float PosX;
uniform float PosY;
uniform float Scale;

void main()
{
	float x = (Position.x / ScreenWidth) * Width;
	float y = (Position.y / ScreenHeight) * Height;
	float posX = PosX / (ScreenWidth * 0.5);
	float posY = PosY / (ScreenHeight * 0.5);

	gl_Position = vec4((x * Scale) + posX, (y * Scale) + posY, 0.0, 1.0);

	TexCoords1 = TexCoords;
}

