#ifndef HIGHSCORES_H
#define HIGHSCORES_H

#include "MySDL.h"
#include "Vector2d.h"

class Highscores {
private:
	Vector2d position;
	char *scores[5][2], nick[24], *path;
	bool isKeyboardLocked = false, shift = false;
	int nhIndex = -1;

	void Save();

public:
	static Highscores* current;

	Highscores(char*);
	~Highscores();

	void Draw();
	void CheckIfHighScore(int);
	bool IsKeyboardLocked();

	void OnKeydownEvent(SDL_Keycode);
};

#endif