#ifndef PADDLE_H
#define PADDLE_H

#include "MySDL.h"
#include "BonusEnabledEvent.h"
#include "BonusDisabledEvent.h"
#include "Collider.h"

class Paddle : public Collider {
private:
	Vector2d position, move;
	SDL_Surface* sprite;
	int wideMode = 0, stickyMode = 0;

public:
	static Paddle* current;

	Paddle(SDL_Surface*);
	~Paddle();

	void Update();
	void Draw();

	void SetPaddle();
	Vector2d GetPosition();
	Vector2d GetMove();
	bool IsSticky();
	bool IsWide();

	void OnKeydownEvent(SDL_Keycode);
	void OnKeyupEvent(SDL_Keycode);
	void OnBonusEnabledEvent(BonusEnabledEvent*);
	void OnBonusDisabledEvent(BonusDisabledEvent*);
	void OnCollision(Collider* const);
};

#endif