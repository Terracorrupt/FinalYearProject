#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2D
{
public:
	Vector2D(float x, float y)
	{
		m_x = x;
		m_y = y;
	}

	float GetX() { return m_x; }
	float GetY() { return m_y; }

	void SetX(float x) { m_x = x; }
	void SetY(float y) { m_y = y; }

	void Add(Vector2D v2)
	{
		m_x += v2.m_x;
		m_y += v2.m_y;
	}

	void Minus(Vector2D v2)
	{
		m_x -= v2.m_x;
		m_y -= v2.m_y;
	}

	void MultiplyBy(Vector2D v2)
	{
		m_x *= v2.m_x;
		m_y *= v2.m_y;
	}

	float m_x;
	float m_y;
};
#endif