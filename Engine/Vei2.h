#pragma once

class Vei2
{
public:
	Vei2() = default;
	Vei2(int in_x, int in_y);
	Vei2 operator+(const Vei2& rhs) const;
	Vei2 operator*(int rhs);
	Vei2 operator-(const Vei2& rhs) const;
public:
	int x;
	int y;
};