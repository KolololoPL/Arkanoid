#include "GameWonEvent.h"

using namespace std;

GameWonEvent::GameWonEvent() {
}

Event::EventType GameWonEvent::GetEventType() {
	return Event::EventType::GameWonEvent;
}

GameWonEvent::~GameWonEvent() {
}
