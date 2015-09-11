#ifndef BOARD_H
#define BOARD_H

#include "Border.h"
#include "Brick.h"
#include "BrickBreakEvent.h"

class Board {
private:
	const int totalBrickCount = BRICK_IN_ROWCOL * BRICK_IN_ROWCOL;
	int nextBoard = 0;
	bool lastPlay = false;

	Border* borders[3];
	Brick* bricks[BRICK_IN_ROWCOL * BRICK_IN_ROWCOL];
	SDL_Surface* brickSprite;

public:
	static Board* current;

	Board(SDL_Surface*);
	~Board();

	void Update();
	void Draw();

	void LoadBoard(const char*);
	void ClearBoard();
	void ResetBoards();
	bool LastPlay();

	void OnBrickBreakEvent(BrickBreakEvent* e);
};

#endif