#include "BonusDisabledEvent.h"

using namespace std;

BonusDisabledEvent::BonusDisabledEvent(Bonus::BonusType bonusType) {
	this->bonusType = bonusType;
}

Bonus::BonusType BonusDisabledEvent::GetBonusType() {
	return bonusType;
}

Event::EventType BonusDisabledEvent::GetEventType() {
	return Event::EventType::BonusDisabledEvent;
}

BonusDisabledEvent::~BonusDisabledEvent() {
}
