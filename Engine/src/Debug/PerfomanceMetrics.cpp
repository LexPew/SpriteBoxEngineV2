#include "Debug/PerformanceMetrics.h"

PerformanceMetrics* PerformanceMetrics::instance{ nullptr };

void PerformanceMetrics::Update(const float p_deltaTime)
{
	FramesPerSecond = 1.0f / p_deltaTime;
	//Increase the frame counter and the timer
	Frames++;
	FramesTimer += p_deltaTime;

	//If we have reached a second or greater calculate the averaged frame-rate and reset the timer
	if (FramesTimer >= FrameSmoothInterval)
	{
		TimeAveragedFramesPerSecond = (SmoothingFactor * TimeAveragedFramesPerSecond) + (1.0f - SmoothingFactor) * (static_cast<float>(Frames) / FramesTimer);
		Frames = 0;
		FramesTimer = 0;
		if (SampleCounter != MaxSamples - 1)
		{
			SampleCounter++;

		}
		else
		{
			SampleCounter = 0;

		}
		FrameSamples[SampleCounter] = TimeAveragedFramesPerSecond;
	}
}
