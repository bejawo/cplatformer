#pragma once

#include <vector>
#include "Graphics.h"
#include "RectI.h"
#include "Surface.h"
#include "Colors.h"
#include "Vei2.h"

class Animation
{
public:
	Animation(int x, int y, int width, int height, int count, const Surface& sprite, float holdTime, Color chroma = Colors::Magenta);
	void draw(Vei2 pos, Graphics& gfx) const;
	void draw(Vei2 pos, Graphics& gfx, const RectI& clip) const;
	void update(float dt);

private:
	void advance();


private:
	std::vector<RectI> frames;
	int iCurFrame = 0;
	float curFrameTime = 0.0f;
	float holdTime;
	const Surface& sprite;
	Color chroma;
};