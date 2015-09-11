#ifndef ARKANOID_H
#define ARKANOID_H

#include "MySDL.h"
#include "Ball.h"
#include "Paddle.h"
#include "Board.h"
#include "Highscores.h"
#include "BonusHandler.h"
#include "GameLoseEvent.h"
#include "GameWonEvent.h"
#include "PointsGotEvent.h"

class Arkanoid {
private:
	//Deklaracja potrzebnych zmiennych
	MySDL* mySDL;
	Ball* balls[MAX_BALLS_ON_BOARD];
	Paddle* paddle;
	Board* board;
	BonusHandler* bonusHandler;
	Highscores* highscores;

	bool isRunning = true;

	//Stan gry
	enum { START, GAME, END, WIN } currentGameState;
	
	void StartGame(bool);

	//Wszystkie potrzebne bitmapy
	enum { BACKGROUND, INTRO, OUTRO, WON_OUTRO, BRICKS, PADDLE, BALL, BONUSES, TOTAL_SPRITES };
	SDL_Surface **sprites;

	//Obsluga zyc
	short lives = 0;
	void ShowLives();

	//Obsluga pileczki
	void AddBall();
	void RemoveBall(Ball*);
	void RemoveBalls();

	//Obsluga punktow
	int points = 0;

	void AddPoints(int);
	void ShowPoints();

public:
	static Arkanoid* current;

	Arkanoid();
	~Arkanoid();

	void Update();
	void Draw();
	
	void AddBall(Vector2d, Vector2d);
	short BallsCount();
	bool IsItBall(Collider*);
	bool IsRunning();

	//Nasluchiwanie zdarzen
	void OnQuitEvent();
	void OnKeydownEvent(SDL_Keycode);
	void OnGameLoseEvent(GameLoseEvent*);
	void OnGameWonEvent(GameWonEvent*);
	void OnPointsGotEvent(PointsGotEvent*);
	void OnBonusEnabledEvent(BonusEnabledEvent*);
	void OnBonusDisabledEvent(BonusDisabledEvent*);
};

#endif