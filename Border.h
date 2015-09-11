#ifndef BORDER_H
#define BORDER_H

#include "Collider.h"

class Border : public Collider {
public:
	Border(Vector2d, int, int);
	~Border();

	void OnCollision(Collider* const);
};

#endif