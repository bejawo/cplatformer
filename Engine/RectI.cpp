#include "RectI.h"


RectI::RectI(int in_left, int in_right, int in_top, int in_bottom)
	:
	left(in_left),
	right(in_right),
	top(in_top),
	bottom(in_bottom)
{
}

RectI::RectI(const Vec2& topLeft, const Vec2& bottomRight) // TODO: create int-based Vec2 class to use instead
	:
	RectI((int)topLeft.x, (int)bottomRight.x, (int)topLeft.y, (int)bottomRight.y)
{
}

RectI::RectI(const Vec2& topLeft, int width, int height)
	:
	RectI(topLeft, topLeft + Vec2((float)width, (float)height))
{
}

bool RectI::isOverlappingWith(const RectI& other) const
{
	return (other.left < right && other.right > left &&
			other.bottom > top && other.top < bottom);
}

int RectI::getWidth() const
{
	return right - left;
}

int RectI::getHeight() const
{
	return bottom - top;
}
