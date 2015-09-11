#ifndef BRICKBREAKEVENT_H
#define BRICKBREAKEVENT_H

#include "Event.h"
#include "Brick.h"

class BrickBreakEvent : public Event{
private:
	Brick* brick;

public:
	BrickBreakEvent(Brick*);
	~BrickBreakEvent();

	Brick* GetBrick();
	EventType GetEventType();
};

#endif