#pragma once
#include "Maths/Vector2.h"

struct Line2
{
	Vector2 start{0,0};
	Vector2 end{0,0};

	Line2() = default;
	Line2(const Vector2& p_start, const Vector2& p_end) : start(p_start), end(p_end) {}
	Line2(const Vector2& p_start, const float p_length, const float p_angle)
	{
		start = p_start;
		end = p_start + Vector2(p_length, 0);
		end.Rotate(p_angle);
	}

	//Returns the intersection point of two lines as a vector.
	static Vector2 LineIntersection(const Line2& lineA, const Line2& lineB)
	{
		const Vector2& p_startA = lineA.start;
		const Vector2& p_endA = lineA.end;
		const Vector2& p_startB = lineB.start;
		const Vector2& p_endB = lineB.end;

		float t = (p_endB.x - p_startB.x) * (p_startB.y - p_startA.y) - (p_endB.y - p_startB.y) * (p_startB.x - p_startA.x);
		t = t / ((p_endB.x - p_startB.x) * (p_endA.y - p_startA.y) - (p_endB.y - p_startB.y) * (p_endA.x - p_startA.x));

		float s = (p_endA.x - p_startA.x) * (p_startB.y - p_startA.y) - (p_endA.y - p_startA.y) * (p_startB.x - p_startA.x);
		s = s / ((p_endB.x - p_startB.x) * (p_endA.y - p_startA.y) - (p_endB.y - p_startB.y) * (p_endA.x - p_startA.x));

		if (t < 0 || t > 1 || s < 0 || s > 1)
		{
			return Vector2(0, 0);
		}

		Vector2 intersectionPoint{ 0,0 };
		intersectionPoint.x = p_startA.x + t * (p_endA.x - p_startA.x);
		intersectionPoint.y = p_startA.y + t * (p_endA.y - p_startA.y);

		return intersectionPoint;
	}
};