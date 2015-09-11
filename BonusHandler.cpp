#include <stdlib.h>
#include <time.h>
#include "BonusHandler.h"
#include "BonusDisabledEvent.h"
#include "EventHandler.h"
#include "Config.h"

using namespace std;

BonusHandler* BonusHandler::current;
Uint32 DisableBonus(Uint32, void*);

BonusHandler::BonusHandler(SDL_Surface* bonusesSprite) {
	//Inicjalizacja potrzebnych zmiennych
	BonusHandler::current = this;
	srand(time(NULL));

	this->bonusesSprite = bonusesSprite;

	//Wyzerowanie bonusow
	for (int x = 0; x < totalBonuses; x++) {
		bonuses[x] = nullptr;
	}

	//Ustawienie typow na ktore potem bedziemy wskazywac
	types[Bonus::BonusType::SlowMode] = Bonus::BonusType::SlowMode;
	types[Bonus::BonusType::StickyPaddle] = Bonus::BonusType::StickyPaddle;
	types[Bonus::BonusType::ExtraLife] = Bonus::BonusType::ExtraLife;
	types[Bonus::BonusType::WidePaddle] = Bonus::BonusType::WidePaddle;
	types[Bonus::BonusType::ThreeBalls] = Bonus::BonusType::ThreeBalls;
}

void BonusHandler::Update() {
	for (int x = 0; x < totalBonuses; x++)
		if (bonuses[x] != nullptr)
			bonuses[x]->Update();

	delay -= MySDL::current->DeltaTime();
}

void BonusHandler::Draw() {
	for (int x = 0; x < totalBonuses; x++)
		if (bonuses[x] != nullptr)
			bonuses[x]->Draw();
}

void BonusHandler::DestroyBonuses() {
	for (int x = 0; x < totalBonuses; x++) {
		if (bonuses[x] != nullptr) {
			delete bonuses[x];
			bonuses[x] = nullptr;
		}
	}
}

void BonusHandler::OnBrickHitedEvent(BrickHitedEvent* e) {
	int chance = BONUS_CHANCE * 100;
	if (rand() % 100 <= chance && delay <= 0) {
		for (int x = 0; x < totalBonuses; x++) {
			if (bonuses[x] == nullptr) {
				int bonusTypeInt = rand() % Bonus::BonusType::TotalBonuses;
				Bonus::BonusType bonusType;

				switch (bonusTypeInt) {
				case 0:
					bonusType = Bonus::BonusType::SlowMode;
					break;
				case 1:
					bonusType = Bonus::BonusType::StickyPaddle;
					break;
				case 2:
					bonusType = Bonus::BonusType::ExtraLife;
					break;
				case 3:
					bonusType = Bonus::BonusType::WidePaddle;
					break;
				case 4:
					bonusType = Bonus::BonusType::ThreeBalls;
					break;
				}

				Vector2d position;
				position = e->GetBrick()->GetOrigin();

				bonuses[x] = new Bonus(bonusesSprite, bonusType, position);
				delay = BONUS_DELAY * 500;

				return;
			}
		}
	}
}

void BonusHandler::OnBonusDestroyEvent(BonusDestroyEvent*e) {
	for (int x = 0; x < totalBonuses; x++) {
		if (bonuses[x] != nullptr) {
			if (bonuses[x]->GetId() == e->GetBonus()->GetId()) {
				delete bonuses[x];
				bonuses[x] = nullptr;
			}
		}
	}
}

void BonusHandler::OnBonusEnabledEvent(BonusEnabledEvent* e) {
	Bonus::BonusType bonusType = e->GetBonusType();
	switch (bonusType) {
		case Bonus::BonusType::SlowMode:
			SDL_AddTimer(20 * 1000, DisableBonus, &types[Bonus::BonusType::SlowMode]);
			break;
		case Bonus::BonusType::StickyPaddle:
			SDL_AddTimer(20 * 1000, DisableBonus, &types[Bonus::BonusType::StickyPaddle]);
			break;
		case Bonus::BonusType::ExtraLife:
			SDL_AddTimer(20 * 1000, DisableBonus, &types[Bonus::BonusType::ExtraLife]);
			break;
		case Bonus::BonusType::WidePaddle:
			SDL_AddTimer(20 * 1000, DisableBonus, &types[Bonus::BonusType::WidePaddle]);
			break;
		case Bonus::BonusType::ThreeBalls:
			SDL_AddTimer(20 * 1000, DisableBonus, &types[Bonus::BonusType::ThreeBalls]);
			break;
	}
}

BonusHandler::~BonusHandler() {
	this->DestroyBonuses();
}

Uint32 DisableBonus(Uint32 interval, void* bonusType) {
	Event* e = new BonusDisabledEvent(*((Bonus::BonusType*) bonusType));
	EventHandler::current->Call(e);

	return 0;
}