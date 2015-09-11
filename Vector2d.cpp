#include <math.h>
#include "Vector2d.h"

using namespace std;

Vector2d::Vector2d() {
	coords.x = 0;
	coords.y = 0;
}

Vector2d::Vector2d(float x, float y) {
	coords.x = x;
	coords.y = y;
}

float Vector2d::GetX() {
	return coords.x;
}

void Vector2d::SetX(float x) {
	coords.x = x;
}

float Vector2d::GetY() {
	return coords.y;
}

void Vector2d::SetY(float y) {
	coords.y = y;
}

float Vector2d::Magnitude() {
	float magnitude = 0;

	magnitude += coords.x * coords.x;
	magnitude += coords.y * coords.y;
	
	magnitude = sqrt(magnitude);
	return magnitude;
}

Vector2d Vector2d::Normalized() {
	Vector2d normalized;

	normalized.SetX(coords.x / this->Magnitude());
	normalized.SetY(coords.y / this->Magnitude());

	return normalized;
}

Vector2d& Vector2d::operator= (Coords c) {
	coords.x = c.x;
	coords.y = c.y;

	return *this;
}

bool operator== (Vector2d a, Vector2d b) {
	if (a.GetX() == b.GetX() && a.GetY() == b.GetY())
		return true;
	return false;
}

Vector2d operator+ (Vector2d a, Vector2d b) {
	float x, y;
	
	x = a.GetX() + b.GetX();
	y = a.GetY() + b.GetY();

	Vector2d r(x, y);
	return r;
}

Vector2d operator- (Vector2d a, Vector2d b) {
	float x, y;

	x = a.GetX() - b.GetX();
	y = a.GetY() - b.GetY();

	Vector2d r(x, y);
	return r;
}

Vector2d operator* (Vector2d a, Vector2d b) {
	float x, y;

	x = a.GetX() * b.GetX();
	y = a.GetY() * b.GetY();

	Vector2d r(x, y);
	return r;
}

Vector2d operator* (Vector2d a, float c) {
	float x, y;

	x = a.GetX() * c;
	y = a.GetY() * c;

	Vector2d r(x, y);
	return r;
}

Vector2d operator/ (Vector2d a, float c) {
	float x, y;

	x = a.GetX() / c;
	y = a.GetY() / c;

	Vector2d r(x, y);
	return r;
}

Vector2d operator* (float c, Vector2d a) {
	float x, y;

	x = a.GetX() * c;
	y = a.GetY() * c;

	Vector2d r(x, y);
	return r;
}

Vector2d operator/ (float c, Vector2d a) {
	float x, y;

	x = a.GetX() / c;
	y = a.GetY() / c;

	Vector2d r(x, y);
	return r;
}