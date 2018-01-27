#include "Animation.h"

Animation::Animation(int x, int y, int width, int height, int count, const Surface& sprite, float holdTime, Color chroma)
	:
	sprite(sprite),
	holdTime(holdTime),
	chroma(chroma)
{
	for (int i = 0; i < count; i++)
	{
		frames.emplace_back(RectI(x + i * width, x + (i + 1) * width, y, y + height));
	}
}

void Animation::draw(Vei2 pos, Graphics& gfx) const
{
	gfx.DrawSprite(pos.x, pos.y, frames[iCurFrame], sprite, chroma);
}

void Animation::draw(Vei2 pos, Graphics& gfx, const RectI& clip) const
{
	gfx.DrawSprite(pos.x, pos.y, frames[iCurFrame], clip, sprite, chroma);
}

void Animation::update(float dt)
{
	curFrameTime += dt;
	while (curFrameTime >= holdTime)
	{
		advance();
		curFrameTime -= holdTime;
	}
}

void Animation::advance()
{
	if (++iCurFrame >= frames.size())
	{
		iCurFrame = 0;
	}
}
