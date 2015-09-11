#include "EventHandler.h"
#include "BonusHandler.h"
#include "Arkanoid.h"
#include "Highscores.h"
#include "Paddle.h"
#include "Ball.h"

using namespace std;

EventHandler* EventHandler::current;

EventHandler::EventHandler() {
	EventHandler::current = this;
}

void EventHandler::HandleSDLEvents() {
	//Wyciagamy eventy i wywolujemy odpowiednie funkcje sluchaczy
	while (SDL_PollEvent(&sdlEvent) != 0) {
		if (sdlEvent.type == SDL_QUIT) {
			Arkanoid::current->OnQuitEvent();
		} else if (sdlEvent.type == SDL_KEYDOWN) {
			if (Highscores::current->IsKeyboardLocked()) {
				if (Highscores::current != nullptr)
					Highscores::current->OnKeydownEvent(sdlEvent.key.keysym.sym);
			} else if (sdlEvent.key.keysym.sym == SDLK_q) {
				Arkanoid::current->OnQuitEvent();
			} else {
				Arkanoid::current->OnKeydownEvent(sdlEvent.key.keysym.sym);
				Paddle::current->OnKeydownEvent(sdlEvent.key.keysym.sym);
			}
		} else if (sdlEvent.type == SDL_KEYUP) {
			Paddle::current->OnKeyupEvent(sdlEvent.key.keysym.sym);
		}
	}
}

void EventHandler::Call(Event* e) {
	if (e->GetEventType() == Event::EventType::GameLoseEvent) {
		Arkanoid::current->OnGameLoseEvent((GameLoseEvent*) e);
	} else if (e->GetEventType() == Event::EventType::GameWonEvent) {
		Arkanoid::current->OnGameWonEvent((GameWonEvent*) e);
	} else if (e->GetEventType() == Event::EventType::BrickHitedEvent) {
		BonusHandler::current->OnBrickHitedEvent((BrickHitedEvent*)e);
	} else if (e->GetEventType() == Event::EventType::BrickBreakEvent) {
		Board::current->OnBrickBreakEvent((BrickBreakEvent*) e);
	} else if (e->GetEventType() == Event::EventType::PointsGotEvent) {
		Arkanoid::current->OnPointsGotEvent((PointsGotEvent*)e);
	} else if (e->GetEventType() == Event::EventType::BonusEnabledEvent) {
		BonusHandler::current->OnBonusEnabledEvent((BonusEnabledEvent*) e);
		Arkanoid::current->OnBonusEnabledEvent((BonusEnabledEvent*) e);
		Paddle::current->OnBonusEnabledEvent((BonusEnabledEvent*) e);
	} else if (e->GetEventType() == Event::EventType::BonusDisabledEvent) {
		Arkanoid::current->OnBonusDisabledEvent((BonusDisabledEvent*) e);
		Paddle::current->OnBonusDisabledEvent((BonusDisabledEvent*) e);
	} else if (e->GetEventType() == Event::EventType::BonusDestroyEvent) {
		BonusHandler::current->OnBonusDestroyEvent((BonusDestroyEvent*) e);
	}
}

EventHandler::~EventHandler() {
}
