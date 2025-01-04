#pragma once

#include <vector>

//Class: PerformanceMetrics
//Purpose: //Handles calculating and returning all performance related metrics, e.g. fps
class PerformanceMetrics
{
private:
	static PerformanceMetrics* instance;

	//Smoothed Average frame rate
	float TimeAveragedFramesPerSecond{ 1 }; //This holds the final averaged fps count
	int Frames{ 0 }; //Increased every update call until reset when FramesTimer reaches 1
	float FramesTimer{ 100.0f }; //Timer that counts up to frameSmoothInterval via delta time
	float SmoothingFactor{ .5f }; //Controls how smooth the fps value is
	float FrameSmoothIntervalStart{ 0 };
	float FrameSmoothInterval{ 0.2f };
	float FramesPerSecond{ 0 };
	//Sampled points
	int MaxSamples{ 50 };

	int SampleCounter{ 0 };
	std::vector<float> FrameSamples;

	/**
	* Creates a new performance metrics object and populates the FrameSamples with 0's
	*/
	PerformanceMetrics()
	{
		//Populate FrameSamples vector with 0's
		for (int sample = 0; sample < MaxSamples; sample++)
		{
			FrameSamples.push_back(0);
		}
		FrameSmoothIntervalStart = FrameSmoothInterval;
	}

public:

	static PerformanceMetrics* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new PerformanceMetrics();
		}
		return instance;
	}


	/**
	 * @return A time smoothed FPS value
	 */
	float GetAveragedFrameRate() const
	{
		return TimeAveragedFramesPerSecond;
	}

	/**
	 * Updates the smoothing factor to the input value
	 * @param p_newSmoothingFactor How smooth FPS should be
	 */
	void SetSmoothingFactor(const float p_newSmoothingFactor)
	{
		SmoothingFactor = p_newSmoothingFactor;
		FrameSmoothInterval = FrameSmoothIntervalStart * (1 + p_newSmoothingFactor);
	}

	float GetSmoothingFactor() const
	{
		return SmoothingFactor;
	}
	/**
	 * @return The max amount of FPS samples taken
	 */
	int GetMaxSamples() const
	{
		return MaxSamples;
	}

	const std::vector<float>& GetSamples() const
	{
		return FrameSamples;
	}

	float GetFrameRate() const
	{
		return FramesPerSecond;
	}

	void Update(const float p_deltaTime);

};