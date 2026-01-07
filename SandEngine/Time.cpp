#include "Time.h"
#include "Math.h"

void Time::Initialize()
{
	currentTime = std::chrono::high_resolution_clock::now();
}

void Time::Update()
{
	previousDeltaTime = deltaTime;
	auto newTime = std::chrono::high_resolution_clock::now();
	deltaTime = std::chrono::duration<float>(newTime - currentTime).count();
	currentTime = newTime;
	time += deltaTime;
}

float Time::Delta()
{
	return deltaTime;
}

float Time::DeltaTimeMS()
{
	return Time::Delta() * 1000;
}

std::chrono::high_resolution_clock::time_point Time::GetCurrentTime()
{
	return std::chrono::high_resolution_clock::now();
}