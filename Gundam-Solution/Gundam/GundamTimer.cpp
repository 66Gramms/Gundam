#include "GundamTimer.h"

using namespace std::chrono;

GundamTimer::GundamTimer()
{
	last = steady_clock::now();
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