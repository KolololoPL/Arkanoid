#include "Bonus.h"
#include "PointsGotEvent.h"
#include "BonusEnabledEvent.h"
#include "BonusDestroyEvent.h"
#include "EventHandler.h"
#include "Paddle.h"
#include "Config.h"

using namespace std;

Bonus::Bonus(SDL_Surface* sprite, Bonus::BonusType bonusType, Vector2d position) : Collider(CollisionFlag::MOVABLE, position, BONUS_SIZE, BONUS_SIZE) {
	this->sprite = sprite;
	this->bonusType = bonusType;
	this->position = position;

	rect.x = 0;
	rect.y = BONUS_SIZE * bonusType;
	rect.w = BONUS_SIZE;
	rect.h = BONUS_SIZE;
}

void Bonus::Update() {
	position = position + Directions::down * BONUS_SPEED * MySDL::current->DeltaTime();
	this->SetOrigin(position);

	if (position.GetY() > SCREEN_HEIGHT + BONUS_SIZE) {
		Event* e = new BonusDestroyEvent(this);
		EventHandler::current->Call(e);
	}
}

void Bonus::Draw() {
	MySDL::current->DrawSprite(sprite, &rect, &position);
}

Bonus::BonusType Bonus::GetBonusType() {
	return bonusType;
}

void Bonus::OnCollision(Collider* const other) {
	if (other->GetId() == Paddle::current->GetId()) {
		Event* e = new BonusEnabledEvent(bonusType);
		EventHandler::current->Call(e);

		e = new PointsGotEvent(BONUS_POINTS + 2 * bonusType);
		EventHandler::current->Call(e);

		e = new BonusDestroyEvent(this);
		EventHandler::current->Call(e);
	}
}

Bonus::~Bonus() {
}
