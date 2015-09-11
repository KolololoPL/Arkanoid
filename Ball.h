#ifndef BALL_H
#define BALL_H

#include "Collider.h"
#include "BonusEnabledEvent.h"
#include "BonusDisabledEvent.h"
#include "Vector2d.h"
#include "MySDL.h"

class Ball : public Collider {
private:
	Vector2d position, move;
	SDL_Surface* sprite;
	bool stickToPaddle = true;
	float pace = 1, deltaX = 0;
	int slowMode = 0;

	void Move();

public:
	Ball(SDL_Surface*);
	Ball(SDL_Surface*, Vector2d, Vector2d);
	~Ball();

	void Update();
	void Draw();

	void SetPace(float);

	void OnKeydownEvent(SDL_Keycode);
	void OnBonusEnabledEvent(BonusEnabledEvent*);
	void OnBonusDisabledEvent(BonusDisabledEvent*);
	void OnCollision(Collider* const);
};

#endif