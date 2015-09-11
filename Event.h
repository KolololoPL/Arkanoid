#ifndef EVENT_H
#define EVENT_H

class Event {
public:
	enum EventType { Generic, GameLoseEvent, GameWonEvent, BrickBreakEvent, BrickHitedEvent, PointsGotEvent, BonusEnabledEvent, BonusDisabledEvent, BonusDestroyEvent };

	Event();
	~Event();

	virtual EventType GetEventType();
};

#endif