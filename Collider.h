#ifndef COLLIDER_H
#define COLLIDER_H

#include "Vector2d.h"

class Collider {
protected:
	unsigned short id;
	Vector2d origin, oldOrigin;
	float width, height;

public:
	enum CollisionFlag { STATIC, MOVABLE };

	Collider(CollisionFlag);
	Collider(CollisionFlag, Vector2d, float, float);
	~Collider();

	void SetOrigin(Vector2d);
	void SetSize(float, float);

	//Punkt blizej (0,0)
	Coords GetTopPoint();
	Coords GetOldTopPoint();
	//Punkt dalej (0,0)
	Coords GetBotPoint();
	Coords GetOldBotPoint();
	//Oba te punkty wyznaczaj¹ prostokat kolizji

	Coords GetOrigin();
	Coords GetOldOrigin();

	unsigned short GetId();
	CollisionFlag GetCollisionFlag();

	virtual void OnCollision(Collider* const) =0;

private:
	CollisionFlag collisionFlag;
};

#endif