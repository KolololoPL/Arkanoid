#include "BonusEnabledEvent.h"

using namespace std;

BonusEnabledEvent::BonusEnabledEvent(Bonus::BonusType bonusType) {
	this->bonusType = bonusType;
}

Bonus::BonusType BonusEnabledEvent::GetBonusType() {
	return bonusType;
}

Event::EventType BonusEnabledEvent::GetEventType() {
	return Event::EventType::BonusEnabledEvent;
}

BonusEnabledEvent::~BonusEnabledEvent() {
}
