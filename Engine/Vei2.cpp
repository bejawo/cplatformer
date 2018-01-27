#include "Vei2.h"

Vei2::Vei2(int in_x, int in_y)
	:
	x(in_x),
	y(in_y)
{
}

Vei2 Vei2::operator+(const Vei2 & rhs) const
{
	return Vei2(x + rhs.x, y + rhs.y);
}

Vei2 Vei2::operator*(int rhs)
{
	return Vei2(x * rhs, y * rhs);
}

Vei2 Vei2::operator-(const Vei2 & rhs) const
{
	return Vei2(x - rhs.x, y - rhs.y);
}
