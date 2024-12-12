#pragma once
#include <algorithm>

#include "Line2.h"
#include "Vector2.h"

class Rect
{
public:

	/**
	 * Holds the left side Y position
	 */
	float Top{0};

	/**
	 * Holds the left side X position
	 */
	float Left{ 0 };


	/**
	 * Holds the right side Y position
	 */
	float Bottom{ 0 };

	/**
	 * Holds the right Side X position
	 */
	float Right{ 0 };

	/**
	 * Holds the width of the rectangle
	 */
	float Width{ 0 };

	/**
	* Holds the height of the rectangle
	 */
	float Height{ 0 };


	/**
	 * Creates a new rectangle with empty values
	 */
	Rect() = default;


	/**
	 * Creates a new rectangle with the input positions
	 */
	Rect(const float p_top, const float p_left, const float p_bottom, const float p_right)
	{
		Create(p_top, p_left, p_bottom, p_right);
	}

	//SERIALIZER
	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(Top, Left, Bottom, Right, Width, Height);
	}

	/**
	 * Setups the rectangle with input values
	 */
	void Create(const float p_top, const float p_left, const float p_bottom, const float p_right)
	{
		Top = p_top;
		Left = p_left;
		Bottom = p_bottom;
		Right = p_right;

		Height = Bottom - Top;
		Width = Right - Left;
	}
	/**
	 * Moves the rectangle's points by the input X and Y
	 */
	void Translate(const float p_directionX, const float p_directionY)
	{
		Top += p_directionY;
		Bottom += p_directionY;

		Left += p_directionX;
		Right += p_directionX;

	}

	/**
	 * Moves the rectangle's points to the given position
	 */
	void SetPosition(const Vector2& p_newPosition)
	{
		Top = p_newPosition.y;
		Left = p_newPosition.x;

		Bottom = p_newPosition.y + Height;
		Right = p_newPosition.x + Width;
	}


	/**
	 * Returns the height
	 */
	float GetWidth() const
	{
		return Width;
	}
	/**
	 * Returns the width
	 */
	float GetHeight() const
	{
		return Height;
	}

	Vector2 Size()
	{
		return { Width, Height };
	}
	/**
	 * Returns the origin point of the rectangle (Top Left coords)
	 */
	Vector2 GetOriginPosition() const
	{
		return { Left,Top };
	}

	/**
	 * Checks to see if this rectangle and the input intersect
	 */
	bool Intersects(const Rect& p_otherBox) const
	{
		return !(Left > p_otherBox.Right ||
			Right < p_otherBox.Left ||
			Top > p_otherBox.Bottom ||
			Bottom < p_otherBox.Top);
	}
	Vector2 CalculatePenetration(const Rect& p_otherBox) const
	{
		// Calculate overlap on each axis
		float overlapX = std::min(Right, p_otherBox.Right) - std::max(Left, p_otherBox.Left);
		float overlapY = std::min(Bottom, p_otherBox.Bottom) - std::max(Top, p_otherBox.Top);

		// Determine the smallest penetration axis
		if (overlapX < overlapY)
		{
			// Penetration along the X-axis
			if (Left < p_otherBox.Left)
			{
				return { -overlapX, 0.0f };
			}
			else
			{
				return { overlapX, 0.0f };
			}
		}
		else
		{
			// Penetration along the Y-axis
			if (Top < p_otherBox.Top)
			{
				return { 0.0f, -overlapY };
			}
			else
			{
				return { 0.0f, overlapY };
			}
		}
	}

	void operator*= (float p_scalar)
	{
		Width *= p_scalar;
		Height *= p_scalar;
	}

	void operator*= (const Vector2& p_vector)
	{
		Width *= p_vector.x;
		Height *= p_vector.y;
	}

	Rect operator* (const Vector2& p_vector) 
	{
		return { Top, Left, Top + Height * p_vector.y, Left + Width * p_vector.x };
	}

	Vector2 RayCastIntersection(const Line2& p_ray)
	{
		// Define the sides of the rectangle
		Line2 topSide{ {Left, Top}, {Right, Top} };
		Line2 leftSide{ {Left, Top}, {Left, Bottom} };
		Line2 rightSide{ {Right, Top}, {Right, Bottom} };
		Line2 bottomSide{ {Left, Bottom}, {Right, Bottom} };

		// Initialize the closest intersection point to a large value
		Vector2 closestIntersectPoint = { std::numeric_limits<float>::max(), std::numeric_limits<float>::max() };
		bool intersectionFound = false;

		// Check intersections with each side of the rectangle
		Vector2 intersectPoint = Line2::LineIntersection(p_ray, topSide);
		if (intersectPoint != Vector2::Zero())
		{
			closestIntersectPoint = intersectPoint;
			intersectionFound = true;
		}

		intersectPoint = Line2::LineIntersection(p_ray, leftSide);
		if (intersectPoint != Vector2::Zero() && Vector2::Distance(p_ray.start, intersectPoint) < Vector2::Distance(p_ray.start, closestIntersectPoint))
		{
			closestIntersectPoint = intersectPoint;
			intersectionFound = true;
		}

		intersectPoint = Line2::LineIntersection(p_ray, rightSide);
		if (intersectPoint != Vector2::Zero() && Vector2::Distance(p_ray.start, intersectPoint) < Vector2::Distance(p_ray.start, closestIntersectPoint))
		{
			closestIntersectPoint = intersectPoint;
			intersectionFound = true;
		}

		intersectPoint = Line2::LineIntersection(p_ray, bottomSide);
		if (intersectPoint != Vector2::Zero() && Vector2::Distance(p_ray.start, intersectPoint) < Vector2::Distance(p_ray.start, closestIntersectPoint))
		{
			closestIntersectPoint = intersectPoint;
			intersectionFound = true;
		}

		// If no intersection was found, return {0, 0}
		if (!intersectionFound)
		{
			return { 0, 0 };
		}

		return closestIntersectPoint;
	}

};

