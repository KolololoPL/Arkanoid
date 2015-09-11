#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include "Collider.h"
#include "Config.h"

class CollisionHandler {
private:
	Collider* staticColliders[TOTAL_STATIC_COLLIDERS];
	Collider* movableColliders[TOTAL_MOVABLE_COLLIDERS];

public:
	static CollisionHandler* current;

	CollisionHandler();
	~CollisionHandler();

	void HandleCollisions();

	unsigned short AddCollider(Collider*);
	bool RemoveCollider(Collider*);

	bool IfCollide(Collider *, Collider *);
};

#endif