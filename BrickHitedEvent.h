#ifndef BRICKHITED_H
#define BRICKHITED_H

#include "Brick.h"
#include "Event.h"

class BrickHitedEvent : public Event {
private:
	Brick* brick;

public:
	BrickHitedEvent(Brick*);
	~BrickHitedEvent();
	
	Brick* GetBrick();
	EventType GetEventType();
};

#endif;