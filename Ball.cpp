#include "Ball.h"
#include "Arkanoid.h"
#include "Paddle.h"
#include "Config.h"
#include "GameLoseEvent.h"
#include "EventHandler.h"

using namespace std;

Ball::Ball(SDL_Surface* sprite) : Collider(CollisionFlag::MOVABLE, position, BALL_RADIUS * 2, BALL_RADIUS * 2) {
	this->sprite = sprite;
	this->move = Directions::up * BALL_SPEED;

	position.SetX(Paddle::current->GetPosition().GetX());
	position.SetY(PADDLE_Y - PADDLE_HEIGHT / 2 - BALL_RADIUS - 1);
	this->SetOrigin(position);
}

Ball::Ball(SDL_Surface* sprite, Vector2d position, Vector2d move) : Collider(CollisionFlag::MOVABLE, position, BALL_RADIUS * 2, BALL_RADIUS * 2) {
	this->sprite = sprite;
	this->position = position;
	this->move = move;

	stickToPaddle = false;
	this->SetOrigin(position);
}

void Ball::Update() {
	//Nadaje ruch pileczce lub utrzymuje ja na paletce
	if (stickToPaddle) {
		position.SetX(Paddle::current->GetPosition().GetX() + deltaX);
		position.SetY(PADDLE_Y - PADDLE_HEIGHT / 2 - BALL_RADIUS - 1);
		this->SetOrigin(position);
	} else {
		this->Move();
	}

	//Wykrywa czy pileczka jest ponad dolna linia ekranu
	if (position.GetY() > SCREEN_WIDTH + BALL_RADIUS * 2) {
		Event* e = new GameLoseEvent(this);
		EventHandler::current->Call(e);
	}

	//Przyspiesza tepo pileczki w czasie
	if (pace >= 1 && !stickToPaddle) {
		pace += BALL_PACE_ACCELERATION * MySDL::current->DeltaTime();
		if (pace > 1.5)
			pace = 1.5;
	}
}

void Ball::Draw() {
	MySDL::current->DrawSprite(sprite, &position);
}

void Ball::SetPace(float pace) {
	this->pace = pace;
}

void Ball::Move() {
	position = position + move * MySDL::current->DeltaTime() * pace;
	this->SetOrigin(position);
}

void Ball::OnKeydownEvent(SDL_Keycode keycode) {
	if (keycode == SDLK_s)
		stickToPaddle = false;
}

void Ball::OnBonusEnabledEvent(BonusEnabledEvent* e) {
	if (e->GetBonusType() == Bonus::BonusType::SlowMode) {
		slowMode++;
		pace = 0.5f;
	} else if (e->GetBonusType() == Bonus::BonusType::ThreeBalls) {
		Arkanoid::current->AddBall(position, (move + Directions::right * 30 + Directions::up* 15).Normalized() * BALL_SPEED);
		Arkanoid::current->AddBall(position, (move + Directions::left * 30 + Directions::down * 15).Normalized() * BALL_SPEED);
	}
}

void Ball::OnBonusDisabledEvent(BonusDisabledEvent* e) {
	if (e->GetBonusType() == Bonus::BonusType::SlowMode) {
		slowMode--;
		if (slowMode <= 0)
			pace = 1;
	}
}

void Ball::OnCollision(Collider* const other) {
	if (other->GetCollisionFlag() == CollisionFlag::STATIC || other->GetId() == Paddle::current->GetId()) {
		Vector2d direction(1, 1);
		//Sprawdzamy z ktorej strony uderzyla i odpowiednio zmieniamy trajektorie
		if (this->GetOldBotPoint().x < other->GetOldTopPoint().x || this->GetOldTopPoint().x > other->GetOldBotPoint().x) {
			//Jesli paletka dogania pileczke, to wcale nie trzeba zmieniac kierunku, trzeba tylko dodac predkosci aby pileczka uciekla
			if (other->GetId() == Paddle::current->GetId() && Paddle::current->GetMove().GetX() * move.GetX() > 0) {
				move.SetX(Paddle::current->GetMove().GetX());
				pace = 1;
			} else {
				direction.SetX(-1);
			}
		}
		if (this->GetOldBotPoint().y < other->GetOldTopPoint().y || this->GetOldTopPoint().y > other->GetOldBotPoint().y)
			direction.SetY(-1);
		move = move * direction;

		if (other->GetId() == Paddle::current->GetId() && direction.GetY() < 0 /*Chodzi nam o -1*/) {
			//Tutaj zmieniamy kat pod jakim ma leciec pilka, jesli udezyla w paletke
			float x = this->GetOrigin().x - other->GetOrigin().x;
			Vector2d offset(x, 0);
			offset = offset * BALL_ANGLE_CHANGE / (Paddle::current->IsWide() ? 2 : 1); //Jesli mamy szeroka paletke, to dzielimy ten kat przez dwa, bo na krancach szerokiej paletki bylby za duzy

			move = move + offset;
			move = move.Normalized() * BALL_SPEED;

			//Kiedy kleisty tryb, to ustawiamy przesuniecie wzgledem x i ze ma byc przyklejona
			if (Paddle::current->IsSticky()) {
				deltaX = position.GetX() - Paddle::current->GetPosition().GetX();
				stickToPaddle = true;
			}
		}

		//Jeden ruch wykonamy, aby zapobiec blednie wykryciu kolejnej kolizji
		this->Move();
	}
}

Ball::~Ball() {
}