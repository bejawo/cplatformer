#pragma once

#include "Vec2.h"

class RectI
{
public:
	RectI() = default;
	RectI(int in_left, int in_right, int in_top, int in_bottom);
	RectI(const Vec2& topLeft, const Vec2& bottomRight);
	RectI(const Vec2& topLeft, int width, int height);

	bool isOverlappingWith(const RectI& other) const;

	int getWidth() const;
	int getHeight() const;

private:
	const int top;
	const int bottom;
	const int left;
	const int right;
};

