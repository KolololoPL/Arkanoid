#include <stdio.h>
#include "Arkanoid.h"
#include "Config.h"

using namespace std;

Arkanoid* Arkanoid::current;

Arkanoid::Arkanoid() {
	Arkanoid::current = this;
	mySDL = MySDL::current;

	for (int x = 0; x < MAX_BALLS_ON_BOARD; x++)
		balls[x] = nullptr;

	sprites = new SDL_Surface*[TOTAL_SPRITES];
	sprites[BACKGROUND] = mySDL->LoadSprite("imgs/background.bmp");
	sprites[INTRO] = mySDL->LoadSprite("imgs/intro.bmp");
	sprites[OUTRO] = mySDL->LoadSprite("imgs/outro.bmp");
	sprites[WON_OUTRO] = mySDL->LoadSprite("imgs/wonoutro.bmp");
	sprites[BRICKS] = mySDL->LoadSprite("imgs/bricks.bmp");
	sprites[PADDLE] = mySDL->LoadSprite("imgs/paddle.bmp");
	sprites[BALL] = mySDL->LoadSprite("imgs/ball.bmp");
	sprites[BONUSES] = mySDL->LoadSprite("imgs/bonuses.bmp");

	paddle = new Paddle(sprites[PADDLE]);
	board = new Board(sprites[BRICKS]);
	highscores = new Highscores("misc/Highscores.txt");
	bonusHandler = new BonusHandler(sprites[BONUSES]);

	currentGameState = START;
}

void Arkanoid::Update() {
	if (currentGameState == GAME) {
		for (int x = 0; x < MAX_BALLS_ON_BOARD; x++)
			if (balls[x] != nullptr)
				balls[x]->Update();
		paddle->Update();
		board->Update();
		bonusHandler->Update();
	}
}

void Arkanoid::Draw() {
	//Pozycja na srodku ekranu
	Vector2d center(SCREEN_WIDTH, SCREEN_HEIGHT);
	center = center / 2;

	//Zaczynamy rysowanie od tla i zyc
	mySDL->DrawSprite(sprites[BACKGROUND], &center);

	//Rysowanie obiektow
	if (currentGameState != START)
		this->ShowPoints();

	if (currentGameState == GAME) {
		this->ShowLives();

		bonusHandler->Draw();
		for (int x = 0; x < MAX_BALLS_ON_BOARD; x++)
			if (balls[x] != nullptr)
				balls[x]->Draw();
		paddle->Draw();
		board->Draw();
	}

	//Wyswietlanie paskow startowego/koncowego
	if (currentGameState == START)
		mySDL->DrawSprite(sprites[INTRO], &center);
	else if (currentGameState == END) {
		mySDL->DrawSprite(sprites[OUTRO], &(center + Directions::up * 50));
		highscores->Draw();
	} else if (currentGameState == WIN) {
		mySDL->DrawSprite(sprites[WON_OUTRO], &(center + Directions::up * 50));
		highscores->Draw();
	}

	//I update ekranu
	mySDL->UpdateScreen();
}

void Arkanoid::StartGame(bool resetAll) {
	this->RemoveBalls();

	if (resetAll) {
		board->ResetBoards();
		lives = LIVES;
		lives--;
		points = 0;
	}

	board->ClearBoard();
	board->LoadBoard("misc/boards.txt");

	paddle->SetPaddle();

	bonusHandler->DestroyBonuses();

	this->AddBall();
	currentGameState = GAME;
}

void Arkanoid::AddBall() {
	for (int x = 0; x < MAX_BALLS_ON_BOARD; x++) {
		if (balls[x] == nullptr) {
			balls[x] = new Ball(sprites[BALL]);
			return;
		}
	}
}

void Arkanoid::AddBall(Vector2d position, Vector2d move) {
	for (int x = 0; x < MAX_BALLS_ON_BOARD; x++) {
		if (balls[x] == nullptr) {
			balls[x] = new Ball(sprites[BALL], position, move);
			return;
		}
	}
}

void Arkanoid::RemoveBall(Ball* ball) {
	for (int x = 0; x < MAX_BALLS_ON_BOARD; x++) {
		if (balls[x] != nullptr) {
			if (balls[x]->GetId() == ball->GetId()) {
				delete balls[x];
				balls[x] = nullptr;
				return;
			}
		}
	}
}

void Arkanoid::RemoveBalls() {
	for (int x = 0; x < MAX_BALLS_ON_BOARD; x++) {
		if (balls[x] != nullptr) {
			delete balls[x];
			balls[x] = nullptr;
		}
	}
}

short Arkanoid::BallsCount() {
	short r = 0;
	for (int x = 0; x < MAX_BALLS_ON_BOARD; x++) {
		if (balls[x] != nullptr)
			r++;
	}

	return r;
}

void Arkanoid::ShowLives() {
	Vector2d textPosition(BORDER_WIDTH + 30, TOP_OFFSET / 2 + 12);
	mySDL->DrawString("Zycia:", &textPosition);

	for (int x = 0; x < lives; x++) {
		Vector2d livesPosition(BORDER_WIDTH + 140 + x * (BALL_RADIUS * 2 + 10), BALL_RADIUS * 2 + TOP_OFFSET / 2);
		mySDL->DrawSprite(sprites[BALL], &livesPosition);
	}
}

void Arkanoid::AddPoints(int points) {
	this->points += points;
}

void Arkanoid::ShowPoints() {
	Vector2d textPosition(BORDER_WIDTH + 30, TOP_OFFSET / 2 - 12);
	mySDL->DrawString("Punkty:", &textPosition);

	char c[10];
	sprintf(c, "%d", points);

	textPosition = textPosition + Directions::right * 16 * 8;
	mySDL->DrawString(c, &textPosition);
}

bool Arkanoid::IsItBall(Collider* collider) {
	for (int x = 0; x < MAX_BALLS_ON_BOARD; x++)
		if (balls[x] != nullptr)
			if (collider->GetId() == balls[x]->GetId())
				return true;
	return false;
}

bool Arkanoid::IsRunning() {
	return isRunning;
}

void Arkanoid::OnQuitEvent() {
	isRunning = false;
}

void Arkanoid::OnKeydownEvent(SDL_Keycode keycode) {
	if (keycode == SDLK_SPACE) {
		if (currentGameState == START)
			this->StartGame(true);
	} else if (keycode == SDLK_r) {
		if (currentGameState == END || currentGameState == WIN)
			this->StartGame(true);
	}

	for (int x = 0; x < MAX_BALLS_ON_BOARD; x++)
		if (balls[x] != nullptr)
			balls[x]->OnKeydownEvent(keycode);
}

void Arkanoid::OnGameLoseEvent(GameLoseEvent* e) {
	this->RemoveBall(e->GetBall());

	if (this->BallsCount() == 0) {
		lives--;
		if (lives < 0) {
			currentGameState = END;
			highscores->CheckIfHighScore(points);
		} else
			this->AddBall();
	}
}

void Arkanoid::OnGameWonEvent(GameWonEvent* e) {
	if (board->LastPlay()) {
		currentGameState = WIN;
		highscores->CheckIfHighScore(points);
	} else {
		this->AddPoints(100);
		this->StartGame(false);
	}
}

void Arkanoid::OnPointsGotEvent(PointsGotEvent* e) {
	this->AddPoints(e->GetPoints());
}

void Arkanoid::OnBonusEnabledEvent(BonusEnabledEvent* e) {
	for (int x = 0; x < MAX_BALLS_ON_BOARD; x++) {
		if (balls[x] != nullptr) {
			balls[x]->OnBonusEnabledEvent(e);
			if (e->GetBonusType() == Bonus::BonusType::ThreeBalls)
				break;
		}
	}

	if (e->GetBonusType() == Bonus::BonusType::ExtraLife && lives < 20)
		lives++;
}

void Arkanoid::OnBonusDisabledEvent(BonusDisabledEvent* e) {
	for (int x = 0; x < MAX_BALLS_ON_BOARD; x++)
		if (balls[x] != nullptr)
			balls[x]->OnBonusDisabledEvent(e);
}

Arkanoid::~Arkanoid() {
	mySDL->CleanSprite(sprites[BACKGROUND]);
	mySDL->CleanSprite(sprites[INTRO]);
	mySDL->CleanSprite(sprites[OUTRO]);
	mySDL->CleanSprite(sprites[WON_OUTRO]);
	mySDL->CleanSprite(sprites[BRICKS]);
	mySDL->CleanSprite(sprites[PADDLE]);
	mySDL->CleanSprite(sprites[BALL]);
	mySDL->CleanSprite(sprites[BONUSES]);

	delete paddle;
	delete board;
	for (int x = 0; x < MAX_BALLS_ON_BOARD; x++)
		if (balls[x] != nullptr)
			delete balls[x];
	delete bonusHandler;
}
