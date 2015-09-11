#include "BrickHitedEvent.h"

using namespace std;

BrickHitedEvent::BrickHitedEvent(Brick* brick) {
	this->brick = brick;
}

Brick* BrickHitedEvent::GetBrick() {
	return brick;
}

Event::EventType BrickHitedEvent::GetEventType() {
	return Event::EventType::BrickHitedEvent;
}

BrickHitedEvent::~BrickHitedEvent() {
}
