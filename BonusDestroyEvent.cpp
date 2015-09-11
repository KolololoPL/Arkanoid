#include "BonusDestroyEvent.h"

using namespace std;

BonusDestroyEvent::BonusDestroyEvent(Bonus* bonus) {
	this->bonus = bonus;
}

Bonus* BonusDestroyEvent::GetBonus() {
	return bonus;
}

Event::EventType BonusDestroyEvent::GetEventType() {
	return Event::EventType::BonusDestroyEvent;
}

BonusDestroyEvent::~BonusDestroyEvent() {
}
