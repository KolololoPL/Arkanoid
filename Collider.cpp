#include "Collider.h"
#include "CollisionHandler.h"

using namespace std;

Collider::Collider(CollisionFlag flag) {
	this->collisionFlag = flag;
	this->id = CollisionHandler::current->AddCollider(this);
}

Collider::Collider(CollisionFlag flag, Vector2d origin, float width, float height) {
	this->collisionFlag = flag;
	this->id = CollisionHandler::current->AddCollider(this);
	this->origin = origin;
	this->oldOrigin = origin;
	this->width = width;
	this->height = height;
}

void Collider::SetOrigin(Vector2d origin) {
	this->oldOrigin = this->origin;
	this->origin = origin;
}

void Collider::SetSize(float width, float height) {
	this->width = width;
	this->height = height;
}

Coords Collider::GetTopPoint() {
	float x, y;

	x = origin.GetX() - (width / 2);
	y = origin.GetY() - (height / 2);

	Coords c = { x, y };
	return c;
}

Coords Collider::GetOldTopPoint() {
	float x, y;

	x = oldOrigin.GetX() - (width / 2);
	y = oldOrigin.GetY() - (height / 2);

	Coords c = { x, y };
	return c;
}

Coords Collider::GetBotPoint() {
	float x, y;

	x = origin.GetX() + (width / 2);
	y = origin.GetY() + (height / 2);

	Coords c = { x, y };
	return c;
}

Coords Collider::GetOldBotPoint() {
	float x, y;

	x = oldOrigin.GetX() + (width / 2);
	y = oldOrigin.GetY() + (height / 2);

	Coords c = { x, y };
	return c;
}

Coords Collider::GetOrigin() {
	Coords c = { origin.GetX(), origin.GetY() };
	return c;
}

Coords Collider::GetOldOrigin() {
	Coords c = { oldOrigin.GetX(), oldOrigin.GetY() };
	return c;
}

unsigned short Collider::GetId() {
	return this->id;
}

Collider::CollisionFlag Collider::GetCollisionFlag() {
	return this->collisionFlag;
}

Collider::~Collider() {
	CollisionHandler::current->RemoveCollider(this);
}
