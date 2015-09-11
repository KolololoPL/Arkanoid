#include "GameLoseEvent.h"

using namespace std;

GameLoseEvent::GameLoseEvent(Ball* ball) {
	this->ball = ball;
}

Ball* GameLoseEvent::GetBall() {
	return ball;
}

Event::EventType GameLoseEvent::GetEventType() {
	return Event::EventType::GameLoseEvent;
}

GameLoseEvent::~GameLoseEvent() {
}
