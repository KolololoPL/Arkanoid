#ifndef BRICK_H
#define BRICK_H

#include "Collider.h"
#include "Vector2d.h"
#include "Config.h"
#include "MySDL.h"

class Brick : public Collider {
private:
	SDL_Surface* sprite;
	Vector2d position;
	SDL_Rect rect;
	short lives, id;

public:
	Brick(SDL_Surface*, Vector2d, short, short);
	~Brick();
	
	void Draw();
	void SetSpriteRect();
	short GetId();
	short GetLives();

	void OnCollision(Collider* const);
};

#endif