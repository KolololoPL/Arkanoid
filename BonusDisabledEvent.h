#ifndef BONUSDISABLEDEVENT_H
#define BONUSDISABLEDEVENT_H

#include "Bonus.h"
#include "Event.h"

class BonusDisabledEvent : public Event {
private:
	Bonus::BonusType bonusType;

public:
	BonusDisabledEvent(Bonus::BonusType);
	~BonusDisabledEvent();

	Bonus::BonusType GetBonusType();
	EventType GetEventType();
};

#endif