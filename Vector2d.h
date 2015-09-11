#ifndef VECTOR2D_H
#define VECTOR2D_H

typedef struct {
	float x, y;
} Coords;

class Vector2d {
private:
	Coords coords;

public:
	Vector2d();
	Vector2d(float, float);

	float GetX();
	void SetX(float);

	float GetY();
	void SetY(float);

	float Magnitude();
	Vector2d Normalized();

	Vector2d& operator= (Coords);
};

bool operator== (Vector2d, Vector2d);

Vector2d operator+ (Vector2d, Vector2d);
Vector2d operator- (Vector2d, Vector2d);
Vector2d operator* (Vector2d, Vector2d);
Vector2d operator* (Vector2d, float);
Vector2d operator/ (Vector2d, float);
Vector2d operator* (float, Vector2d);
Vector2d operator/ (float, Vector2d);

namespace Directions {
	const static Vector2d left(-1, 0), right(1, 0), up(0, -1), down(0, 1), still(0, 0);
}

#endif