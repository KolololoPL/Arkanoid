#ifndef GAMEWONEVENT_H
#define GAMEWONEVENT_H

#include "Event.h"

class GameWonEvent : public Event {
public:
	GameWonEvent();
	~GameWonEvent();

	EventType GetEventType();
};

#endif