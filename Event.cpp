#include "Event.h"

using namespace std;

Event::Event() {
}

Event::EventType Event::GetEventType() {
	return Event::EventType::Generic;
}

Event::~Event() {
}
