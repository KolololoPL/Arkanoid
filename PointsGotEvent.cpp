#include "PointsGotEvent.h"

using namespace std;

PointsGotEvent::PointsGotEvent(int points) {
	this->points = points;
}

int PointsGotEvent::GetPoints() {
	return points;
}

Event::EventType PointsGotEvent::GetEventType() {
	return Event::EventType::PointsGotEvent;
}

PointsGotEvent::~PointsGotEvent() {
}
