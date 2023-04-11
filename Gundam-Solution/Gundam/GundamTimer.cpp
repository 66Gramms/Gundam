#include "GundamTimer.h"

using namespace std::chrono;

GundamTimer::GundamTimer()
{
	last = steady_clock::now();
	lastFrame = last;
}

float GundamTimer::Mark()
{
	const steady_clock::time_point old = last;
	last = steady_clock::now();
	const duration<float> frameTime = last - old;
	return frameTime.count();
}

float GundamTimer::Peek() const
{
	return duration<float>(steady_clock::now() - last).count();
}

float GundamTimer::DeltaTime()
{
	duration<float> deltaTime = steady_clock::now() - lastFrame;
	lastFrame = steady_clock::now();
	return deltaTime.count();
}