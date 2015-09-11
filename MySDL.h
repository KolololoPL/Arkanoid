#ifndef MYSDL_H
#define MYSDL_H

#include <SDL.h>
#include "Vector2d.h"

class MySDL {
private:
	SDL_Window *window = NULL;
	SDL_Surface *screen = NULL, *charset = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Texture *texture = NULL;

	unsigned int oldTime = 0, newTime = 0;

public:
	static MySDL *current;

	MySDL(const int, const int, const char *);
	~MySDL();

	SDL_Surface* LoadSprite(char *);
	void CleanSprite(SDL_Surface*);

	void DrawSprite(SDL_Surface*, int, int);
	void DrawSprite(SDL_Surface*, Vector2d*);
	void DrawSprite(SDL_Surface*, SDL_Rect*, int, int);
	void DrawSprite(SDL_Surface*, SDL_Rect*, Vector2d*);

	void DrawString(char *, int, int);
	void DrawString(char *, Vector2d*);

	//Zwraca ile sekund minelo od ostatniego updatu
	float DeltaTime();

	void UpdateScreen();
	void UpdateTime();
};

#endif