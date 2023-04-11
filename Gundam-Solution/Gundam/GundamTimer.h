#pragma once
#include <chrono>

class GundamTimer
{
public:
	GundamTimer();
	float Mark();
	float Peek() const;
	float DeltaTime();
private:
	std::chrono::steady_clock::time_point last;
	std::chrono::steady_clock::time_point lastFrame;
};