#include "FrameTimer.h"

using namespace std::chrono;

FrameTimer::FrameTimer()
{
	steady_clock::time_point last = steady_clock::now();
}

float FrameTimer::Mark()
{
	steady_clock::time_point old = last;
	last = steady_clock::now();
	duration<float> frameTime = last - old;

	return frameTime.count();
}
