#ifndef POINTSGOTEVENT_H
#define POINTSGOTEVENT_H

#include "Event.h"

class PointsGotEvent : public Event {
private:
	int points;

public:
	PointsGotEvent(int);
	~PointsGotEvent();

	int GetPoints();
	EventType GetEventType();
};

#endif