#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <SDL.h>
#include "Event.h"

class EventHandler {
private:
	SDL_Event sdlEvent;

public:
	static EventHandler* current;

	EventHandler();
	~EventHandler();

	void HandleSDLEvents();
	void Call(Event*);
};

#endif