#ifndef BONUSENABLED_H
#define BONUSENABLED_H

#include "Bonus.h"
#include "Event.h"

class BonusEnabledEvent : public Event {
private:
	Bonus::BonusType bonusType;

public:
	BonusEnabledEvent(Bonus::BonusType);
	~BonusEnabledEvent();

	Bonus::BonusType GetBonusType();
	EventType GetEventType();
};

#endif