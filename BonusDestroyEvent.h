#ifndef BONUSDESTROYEVENT_H
#define BONUSDESTROYEVENT_H

#include "Bonus.h"
#include "Event.h"

class BonusDestroyEvent : public Event {
private:
	Bonus* bonus;

public:
	BonusDestroyEvent(Bonus*);
	~BonusDestroyEvent();

	Bonus* GetBonus();
	EventType GetEventType();
};

#endif