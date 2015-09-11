#ifndef BONUS_H
#define BONUS_H

#include "MySDL.h"
#include "Vector2d.h"
#include "Collider.h"

class Bonus : public Collider {
private:
	SDL_Surface* sprite;
	SDL_Rect rect;
	Vector2d position;

public:
	enum BonusType {SlowMode, StickyPaddle, ExtraLife, WidePaddle, ThreeBalls, TotalBonuses};

	Bonus(SDL_Surface*, BonusType, Vector2d);
	~Bonus();

	void Update();
	void Draw();

	BonusType GetBonusType();

	void OnCollision(Collider* const);

private:
	BonusType bonusType;
};

#endif