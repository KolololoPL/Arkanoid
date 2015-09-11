#include "Paddle.h"
#include "Config.h"

#include <stdio.h>

using namespace std;

Paddle* Paddle::current;

Paddle::Paddle(SDL_Surface* sprite) : Collider(CollisionFlag::MOVABLE, position, PADDLE_WIDTH, PADDLE_HEIGHT) {
	Paddle::current = this;
	this->sprite = sprite;
}

void Paddle::Update() {
	position = position + move * MySDL::current->DeltaTime();
	this->SetOrigin(position);
}

void Paddle::Draw() {
	if (wideMode > 0)
		MySDL::current->DrawSprite(sprite, &(position + Directions::left * PADDLE_WIDTH / 2));

	MySDL::current->DrawSprite(sprite, &position);

	if (wideMode > 0)
		MySDL::current->DrawSprite(sprite, &(position + Directions::right * PADDLE_WIDTH / 2));
}

void Paddle::SetPaddle() {
	Coords startPosition = { SCREEN_WIDTH / 2, PADDLE_Y };
	position = startPosition;

	wideMode = 0;
	stickyMode = 0;

	this->SetOrigin(position);
}

Vector2d Paddle::GetPosition() {
	return position;
}

Vector2d Paddle::GetMove() {
	return move;
}

bool Paddle::IsSticky() {
	if (stickyMode > 0)
		return true;
	return false;
}

bool Paddle::IsWide() {
	if (wideMode > 0)
		return true;
	return false;
}

void Paddle::OnKeydownEvent(SDL_Keycode keycode) {
	if (keycode == SDLK_LEFT)
		move = Directions::left * PADDLE_SPEED;
	else if (keycode == SDLK_RIGHT)
		move = Directions::right * PADDLE_SPEED;
}

void Paddle::OnKeyupEvent(SDL_Keycode keycode) {
	if ((keycode == SDLK_LEFT && move.GetX() < 0) || (keycode == SDLK_RIGHT && move.GetX() > 0))
		move.SetX(0);
}

void Paddle::OnBonusEnabledEvent(BonusEnabledEvent* e) {
	if (e->GetBonusType() == Bonus::BonusType::WidePaddle) {
		wideMode++;
		this->SetSize(PADDLE_WIDTH * 2, PADDLE_HEIGHT);
	} else if (e->GetBonusType() == Bonus::BonusType::StickyPaddle) {
		stickyMode++;
	}
}

void Paddle::OnBonusDisabledEvent(BonusDisabledEvent* e) {
	if (e->GetBonusType() == Bonus::BonusType::WidePaddle) {
		if (wideMode > 0)
			wideMode--;
		if (wideMode <= 0)
			this->SetSize(PADDLE_WIDTH, PADDLE_HEIGHT);
	} else if (e->GetBonusType() == Bonus::BonusType::StickyPaddle) {
		if (stickyMode > 0)
			stickyMode--;
	}
}

void Paddle::OnCollision(Collider* const other) {
	if (other->GetCollisionFlag() == CollisionFlag::STATIC) {
		move.SetX(0);

		if (position.GetX() < SCREEN_WIDTH / 2)
			position.SetX(BORDER_WIDTH + PADDLE_WIDTH * (wideMode > 0 ? 2 : 1) / 2 + 1);
		else
			position.SetX(SCREEN_WIDTH - BORDER_WIDTH - PADDLE_WIDTH * (wideMode > 0 ? 2 : 1) / 2 - 1);

		this->SetOrigin(position);
	}
}

Paddle::~Paddle() {
}