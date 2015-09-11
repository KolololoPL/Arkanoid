#include "BrickBreakEvent.h"

using namespace std;

BrickBreakEvent::BrickBreakEvent(Brick* brick) {
	this->brick = brick;
}

Brick* BrickBreakEvent::GetBrick() {
	return brick;
}

Event::EventType BrickBreakEvent::GetEventType() {
	return Event::EventType::BrickBreakEvent;
}

BrickBreakEvent::~BrickBreakEvent() {
}
