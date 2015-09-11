#include "CollisionHandler.h"

using namespace std;

CollisionHandler* CollisionHandler::current;

CollisionHandler::CollisionHandler() {
	CollisionHandler::current = this;

	for (int x = 0; x < TOTAL_STATIC_COLLIDERS; x++)
		staticColliders[x] = nullptr;
	for (int x = 0; x < TOTAL_MOVABLE_COLLIDERS; x++)
		movableColliders[x] = nullptr;
}

void CollisionHandler::HandleCollisions() {
	for (int m = 0; m < TOTAL_MOVABLE_COLLIDERS; m++) {
		if (movableColliders[m] != nullptr) {
			for (int s = 0; s < TOTAL_STATIC_COLLIDERS; s++) {
				if (staticColliders[s] != nullptr) {
					if (IfCollide(movableColliders[m], staticColliders[s])) {
						movableColliders[m]->OnCollision(staticColliders[s]);
						staticColliders[s]->OnCollision(movableColliders[m]);
					}
				}
			}

			for (int m2 = m + 1; m2 < TOTAL_MOVABLE_COLLIDERS; m2++) {
				if (movableColliders[m2] != nullptr) {
					if (IfCollide(movableColliders[m], movableColliders[m2])) {
						movableColliders[m]->OnCollision(movableColliders[m2]);
						movableColliders[m2]->OnCollision(movableColliders[m]);
					}
				}
			}
		}
	}
}

unsigned short CollisionHandler::AddCollider(Collider* collider) {
	if (collider->GetCollisionFlag() == Collider::CollisionFlag::STATIC) {
		int i = 0;
		while (staticColliders[i] != nullptr)
			i++;
		staticColliders[i] = collider;
		return i;
	} else if (collider->GetCollisionFlag() == Collider::CollisionFlag::MOVABLE) {
		int i = 0;
		while (movableColliders[i] != nullptr)
			i++;
		movableColliders[i] = collider;
		return i + TOTAL_STATIC_COLLIDERS;
	}

	return TOTAL_STATIC_COLLIDERS + TOTAL_MOVABLE_COLLIDERS + 1;
}

bool CollisionHandler::RemoveCollider(Collider* collider) {
	int i = collider->GetId();
	
	if (collider->GetCollisionFlag() == Collider::CollisionFlag::STATIC) {
		if (staticColliders[i] != nullptr) {
			staticColliders[i] = nullptr;
			return true;
		}
	}
	else if (collider->GetCollisionFlag() == Collider::CollisionFlag::MOVABLE) {
		if (movableColliders[i - TOTAL_STATIC_COLLIDERS] != nullptr) {
			movableColliders[i - TOTAL_STATIC_COLLIDERS] = nullptr;
			return true;
		}
	}
	
	return false;
}

bool CollisionHandler::IfCollide(Collider* c1, Collider* c2) {
	if (c1->GetBotPoint().y < c2->GetTopPoint().y)
		return false;
	else if (c1->GetTopPoint().y > c2->GetBotPoint().y)
		return false;
	else if (c1->GetBotPoint().x < c2->GetTopPoint().x)
		return false;
	else if (c1->GetTopPoint().x > c2->GetBotPoint().x)
		return false;

	return true;
}

CollisionHandler::~CollisionHandler() {
}
