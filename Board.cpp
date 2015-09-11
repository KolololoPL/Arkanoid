#include <stdio.h>
#include "Board.h"
#include "Config.h"
#include "GameWonEvent.h"
#include "EventHandler.h"

using namespace std;

Board* Board::current;

Board::Board(SDL_Surface* brickSprite) {
	Board::current = this;
	
	this->brickSprite = brickSprite;

	//Wstepne wypelnianie tablicy cegielek
	for (int x = 0; x < totalBrickCount; x++)
		bricks[x] = nullptr;

	//Ustawienie scian: 0 - gorna, 1 - lewa, 2 - prawa
	Vector2d borderPosition(SCREEN_WIDTH / 2, TOP_OFFSET + BORDER_WIDTH / 2);
	borders[0] = new Border(borderPosition, SCREEN_WIDTH, BORDER_WIDTH);

	borderPosition.SetY(SCREEN_HEIGHT / 2);
	borderPosition.SetX(BORDER_WIDTH / 2);
	borders[1] = new Border(borderPosition, BORDER_WIDTH, SCREEN_HEIGHT);

	borderPosition.SetX(SCREEN_WIDTH - BORDER_WIDTH / 2);
	borders[2] = new Border(borderPosition, BORDER_WIDTH, SCREEN_HEIGHT);
}

void Board::Update() {
	//Pilnuje zakonczenia gry
	for (int x = 0; x < totalBrickCount; x++)
		if (bricks[x] != nullptr)
			return;

	Event* e = new GameWonEvent();
	EventHandler::current->Call(e);
}

void Board::Draw() {
	for (int x = 0; x < totalBrickCount; x++)
		if (bricks[x] != nullptr)
			bricks[x]->Draw();
}

void Board::LoadBoard(const char* path) {
	FILE* file = fopen(path, "rb");
	if (file == NULL) {
		perror(path);
		return;
	}

	int c = fgetc(file), id = 0;
	bool read = false;

	while (c != EOF) {
		if (c == '.' && read) {
			if (id < totalBrickCount) {
				id++;
			} else {
				read = false;
			}
		} else if (c >= 'A' && c <= 'F' && read) {
			if (id < totalBrickCount) {
				int x = BORDER_WIDTH + (BRICK_WIDTH / 2) + ((id % BRICK_IN_ROWCOL) * BRICK_WIDTH);
				int y = TOP_OFFSET + BORDER_WIDTH + (BRICK_HEIGHT / 2) + ((id / BRICK_IN_ROWCOL) * BRICK_HEIGHT);

				short lives = c - 'A';
				Vector2d position(x, y);

				bricks[id] = new Brick(brickSprite, position, lives, id);
				id++;
			} else {
				read = false;
			}
		} else if (c == ':') {
			c = fgetc(file);
			int maxBoards = 0;
			while (c != ':') {
				maxBoards *= 10;
				maxBoards += c - '0';
				c = fgetc(file);
			}
				
			if (nextBoard == maxBoards - 1)
				lastPlay = true;
		} else if (c == '/') {
			c = fgetc(file);
			int currentBoard = 0;
			while (c != '/') {
				currentBoard *= 10;
				currentBoard += c - '0';
				c = fgetc(file);
			}

			if (nextBoard == currentBoard)
				read = true;
		}

		c = fgetc(file);
	}

	fclose(file);
	nextBoard++;
}

void Board::ClearBoard() {
	for (int x = 0; x < totalBrickCount; x++) {
		if (bricks[x] != nullptr) {
			delete bricks[x];
			bricks[x] = nullptr;
		}
	}
}

void Board::ResetBoards() {
	nextBoard = 0;
	lastPlay = false;
}

bool Board::LastPlay() {
	return lastPlay;
}

void Board::OnBrickBreakEvent(BrickBreakEvent* e) {
	const short id = e->GetBrick()->GetId();
	if (bricks[id] != nullptr) {
		delete bricks[id];
		bricks[id] = nullptr;
	}
}

Board::~Board() {
	delete borders[0];
	delete borders[1];
	delete borders[2];

	this->ClearBoard();
}
