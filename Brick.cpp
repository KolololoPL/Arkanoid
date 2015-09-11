#include "Brick.h"
#include "Arkanoid.h"
#include "BrickBreakEvent.h"
#include "BrickHitedEvent.h"
#include "PointsGotEvent.h"
#include "EventHandler.h"

using namespace std;

Brick::Brick(SDL_Surface* sprite, Vector2d position, short lives, short id) : Collider(CollisionFlag::STATIC, position, BRICK_WIDTH, BRICK_HEIGHT) {
	this->sprite = sprite;
	this->position = position;
	this->lives = lives;
	this->id = id;

	this->SetSpriteRect();
}

void Brick::Draw() {
	MySDL::current->DrawSprite(sprite, &rect, &position);
}

void Brick::SetSpriteRect() {
	rect.x = 0;
	rect.y = lives * BRICK_HEIGHT;
	rect.w = BRICK_WIDTH;
	rect.h = BRICK_HEIGHT;
}

short Brick::GetId() {
	return id;
}

short Brick::GetLives() {
	return lives;
}

void Brick::OnCollision(Collider* const other) {
	if (Arkanoid::current->IsItBall(other)) {
		Event* e = new PointsGotEvent(lives + 1);
		EventHandler::current->Call(e);

		e = new BrickHitedEvent(this);
		EventHandler::current->Call(e);

		lives--;

		if (lives < 0) {
			e = new BrickBreakEvent(this);
			EventHandler::current->Call(e);
		}
		else {
			this->SetSpriteRect();
		}
	}
}

Brick::~Brick() {
}
