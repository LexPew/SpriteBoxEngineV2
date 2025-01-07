#pragma once
#include <cmath>
#include <ostream>

struct Vector2
{
public:
	float x{ 0 };
	float y{ 0 };

	
	/**
	 * Creates a Vector2 struct with the default values 0,0
	 */
	Vector2() = default;
	/**
	 * Creates a Vector2 struct with the input values
	 */
	Vector2(const float p_xInput, const float p_yInput)
	{
		x = p_xInput;
		y = p_yInput;
	}



	//SERIALIZER
	template <class Archive>
	void serialize(Archive& p_archive)
	{
		p_archive(x, y);
	}

	void Clear()
	{
		x = 0;
		y = 0;
	}
	/**
	 * Returns a copy of the two vectors added together
	 * @param p_vectorB Vector to add to this
	 * @return Finished operation
	 */
	Vector2 operator+(Vector2 const& p_vectorB) const
	{
		return {x + p_vectorB.x, y + p_vectorB.y};
	}

	// Overload the += operator
	void operator+=(const Vector2& p_vectorB)
	{
		//Adding two vectors is like placing them end to end and ending up in a point from the origin equalling the two
		x += p_vectorB.x;
		y += p_vectorB.y;
	}

	// Overload the += operator
	void operator+=(const float p_scalar)
	{
		
		x += p_scalar;
		y += p_scalar;
	}

	bool operator!=(const Vector2& p_vectorB) const
	{
		return (x != p_vectorB.x || y != p_vectorB.y);
	}

	float operator%(const Vector2& p_vectorB) const
	{
		//Formula for cross product in 2d space AxB = X1 * Y2 - Y1 * X2 resulting in scalar
		//AxB > 0 B is counterclockwise from A
		//AxB < 0 B is clockwise from A
		//AxB == 0 A and B are collinear
		return x * p_vectorB.y - y * p_vectorB.x;
	}
	/**
	 * Subtracts another Vector from this Vector
	 * @param p_vectorB Vector to subtract from this
	 * @return Finished operation
	 */
	Vector2 operator-(Vector2 const& p_vectorB) const
	{
		return {x - p_vectorB.x, y - p_vectorB.y};
	}

	/**
	 * 
	 * @return Inverse version of the vector
	 */
	Vector2 operator-() const
	{
		return {-x,-y};
	}

	void AddScaledVector(const Vector2& p_VectorB, const float p_scalar)
	{
		x += p_VectorB.x * p_scalar;
		y += p_VectorB.y * p_scalar;

	}


	/**
	* Multiplies both axis by the input scalar value
	* @param p_scalar Multiplier
	*/
	void operator*=(float const p_scalar) 
	{
		//Multiplies the vector by a scalar (x,y) * k = (kx,ky) k being the scalar value
		//Basically just multiply all component values by the scalar

		//Just changes the magnitude by multiplying by scalar but not the direction so ka = (k*|a|)*n^
		x = x * p_scalar;
		y = y * p_scalar;
	}


	/**
	 * Returns a copy of this vector scaled by the given value
	 * @param p_scalar Multiplier
	 * @return Finished operation
	 */
	Vector2 operator*(float const p_scalar) const
	{
		//Multiplies the vector by a scalar (x,y) * k = (kx,ky) k being the scalar value
		//Basically just multiply all component values by the scalar 
		return { x * p_scalar, y * p_scalar };
	}

	float operator*(Vector2 const p_vectorB) const
	{
		//Dot /Scalar product formula
		//a.b = (ax,ay).(bx,by) = (ax*bx)+(ay*by) 
		//Scalar product or commonly know as dot product due to A.B being the notation  
		return { (x * p_vectorB.x) + (y * p_vectorB.y) }; 
	}
	/**
	 * Compares two vectors to check whether they are equal
	 * @param p_vectorB Vector to compare
	 * @return 
	 */
	bool operator==(const Vector2& p_vectorB) const
	{
		return (x == p_vectorB.x && y == p_vectorB.y);
	}

	/**
	 * Divides the vector by the denominator input
	 * @return Copy of this vector divided by input
	 */
	Vector2 operator/(const float p_denominator) const
	{
		//Same as multiplication you just divide each component (numerators) by the scalar (denominator) = (x/k, y/k) k being scalar value
		return { x / p_denominator, y / p_denominator };
	}

	//Overload the << operator
	friend std::ostream& operator<<(std::ostream& p_stream, const Vector2& p_vector)
	{
		p_stream << "X: " << p_vector.x << " Y: " << p_vector.y;
		return p_stream;
	}

	/**
	 * Calculates and returns a component product of this vector with a given vector
	 * @return Copy of this vector component product
	 */
	Vector2 ComponentProduct(const Vector2& p_vectorB) const
	{
		return { x * p_vectorB.x, y * p_vectorB.y };
	}

	/**
	* Calculates and returns a component product of this vector with a given vector
	* and updates the values of this vector to its result
	*/
	void ComponentProductUpdate(const Vector2& p_vectorB)
	{
		x *= p_vectorB.x;
		y *= p_vectorB.y;
	}
	Vector2 Inverse() const
	{
		//Formula for inverse ->-a = -1 * a = (-1x,-1y)
		Vector2 inverse = { x,y };
		inverse = inverse * -1;
		return inverse;
	}
	/**
	 * @return The magnitude of the vector
	 */
	float Magnitude() const
	{
		//|V| = sqrt(a^2 + b^2)
		//To get magnitude square both components and add them then find sqrt
		return std::sqrt(x * x + y * y);
		
	}

	/**
	 * @return A normalized Vector2
	 */
	Vector2 Normalize() const
	{
		//Normalized vector or the unit vector (kinda)
		//To get normalized vector divide each component by its magnitude

		//Formula for normalization = 
		const float mag = Magnitude();
		return { x / mag, y / mag };
	}

	static Vector2 Zero()
	{
		return { 0,0 };
	}
	static Vector2 One()
	{
		return { 1,1 };
	}
	void Lerp(const Vector2& p_vectorB, const float p_factor) 
	{
		x = (x * (1.0f - p_factor) + (p_vectorB.x * p_factor));
		y = (y * (1.0f - p_factor) + (p_vectorB.y * p_factor));

	}


	/**
	 * Finds the distance between two input vectors
	 * @return Distance in floating point
	 */
	static inline float Distance(const Vector2& p_vectorA, const Vector2& p_vectorB)
	{
		// Correct formula: square of the differences
		const float deltaX = p_vectorA.x - p_vectorB.x;
		const float deltaY = p_vectorA.y - p_vectorB.y;

		// Now apply the correct distance formula
		const float distance = sqrt((deltaX * deltaX) + (deltaY * deltaY));

		return distance;
	}

	

	static inline float Angle(const Vector2& p_vectorA, const Vector2& p_vectorB)
	{
		const float dot = p_vectorA * p_vectorB;

		const float magA = p_vectorA.Magnitude();
		const float magB = p_vectorB.Magnitude();

		const float angleInRadians = acos(dot / (magA * magB));

		const float angleInDegrees = angleInRadians * 57.29f; // 
		return angleInDegrees;
	}

	void Rotate(const float p_angle)
	{
		//Radian = degrees * pie / 180
		//degrees = radian * (pie / 180)
		const float radianAngle = p_angle * 3.14159f / 180.0f;
		const float xComponent = x * cos(radianAngle) - y * sin(radianAngle);
		const float yComponent = x * sin(radianAngle) + y * cos(radianAngle);
		x = xComponent;
		y = yComponent;
	}

	float GetAngle() const
	{
		return (atan2(x, y) * 57.29f);
	}
};


