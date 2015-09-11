#ifndef BONUSHANDLER_H
#define BONUSHANDLER_H

#include "Config.h"
#include "BrickHitedEvent.h"
#include "BonusDestroyEvent.h"
#include "BonusEnabledEvent.h"

class BonusHandler {
private:
	SDL_Surface* bonusesSprite;
	const int totalBonuses = TOTAL_MOVABLE_COLLIDERS - 7;
	Bonus* bonuses[TOTAL_MOVABLE_COLLIDERS - 7];
	int delay = 0;

	Bonus::BonusType types[Bonus::BonusType::TotalBonuses];

public:
	static BonusHandler* current;

	BonusHandler(SDL_Surface*);
	~BonusHandler();

	void Update();
	void Draw();
	
	void DestroyBonuses();

	void OnBrickHitedEvent(BrickHitedEvent*);
	void OnBonusDestroyEvent(BonusDestroyEvent*);
	void OnBonusEnabledEvent(BonusEnabledEvent*);
};

#endif