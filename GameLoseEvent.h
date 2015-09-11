#ifndef GAMELOSEEVENT_H
#define GAMELOSEEVENT_H

#include "Event.h"
#include "Ball.h"

class GameLoseEvent : public Event {
private:
	Ball* ball;

public:
	GameLoseEvent(Ball*);
	~GameLoseEvent();

	Ball* GetBall();
	Event::EventType GetEventType();
};

#endif