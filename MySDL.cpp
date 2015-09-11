#include <stdio.h>
#include "MySDL.h"
#include "Config.h"

using namespace std;

MySDL *MySDL::current;

MySDL::MySDL(const int screenWidth, const int screenHeight, const char *title) {
	MySDL::current = this;

	//Inicjalizacja SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
	} else {
		//Tworzymy okno
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		} else {
			renderer = SDL_CreateRenderer(window, -1, 0);
		}

		//Tworzymy p³aszczyznê na nasze bitmapy
		screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
		if (screen == NULL) {
			printf("CreateRGBSurface failed: %s\n", SDL_GetError());
		}

		//Tworzymy teksturê do wyœwietlania
		texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
		if (texture == NULL) {
			printf("CreateTexture failed: %s\n", SDL_GetError());
		}

		//Ustawiamy skalowanie tekstur
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
		SDL_RenderSetLogicalSize(renderer, screenWidth, screenHeight);

	}

	//Ustawianie czasu startowego
	oldTime = SDL_GetTicks();
	newTime = oldTime;

	//Zaladowanie charset-u
	charset = this->LoadSprite("imgs/cs8x8.bmp");
}

SDL_Surface* MySDL::LoadSprite(char * path) {
	SDL_Surface* optimalizedSprite = NULL;
	SDL_Surface* loadedSprite = SDL_LoadBMP(path);

	if (loadedSprite == NULL) {
		printf("Unable to load image %s! SDL Error: %s\n", path, SDL_GetError());
	} else {
		//Konwersja sprita do formatu ekranu
		optimalizedSprite = SDL_ConvertSurface(loadedSprite, screen->format, NULL);
		if (optimalizedSprite == NULL)
		{
			printf("Unable to optimize image %s! SDL Error: %s\n", path, SDL_GetError());
		}

		SDL_FreeSurface(loadedSprite);
	}

	return optimalizedSprite;
}

void MySDL::CleanSprite(SDL_Surface* sprite) {
	SDL_FreeSurface(sprite);
	sprite = NULL;
}

void MySDL::DrawSprite(SDL_Surface* sprite, int x, int y) {
	SDL_Rect destination;

	destination.x = x - sprite->w / 2;
	destination.y = y - sprite->h / 2;
	destination.w = sprite->w;
	destination.h = sprite->h;

	SDL_BlitSurface(sprite, NULL, screen, &destination);
}

void MySDL::DrawSprite(SDL_Surface* sprite, Vector2d* position) {
	this->DrawSprite(sprite, position->GetX(), position->GetY());
}

void MySDL::DrawSprite(SDL_Surface* sprite, SDL_Rect* rect, int x, int y) {
	SDL_Rect destination;

	destination.x = x - rect->w / 2;
	destination.y = y - rect->h / 2;
	destination.w = rect->w;
	destination.h = rect->h;

	SDL_BlitSurface(sprite, rect, screen, &destination);
}

void MySDL::DrawSprite(SDL_Surface* sprite, SDL_Rect* rect, Vector2d* position) {
	this->DrawSprite(sprite, rect, position->GetX(), position->GetY());
}

void MySDL::DrawString(char* text, int x, int y) {
	int px, py, c;
	SDL_Rect s, d;
	s.w = 16;
	s.h = 16;
	d.w = 16;
	d.h = 16;

	while (*text) {
		c = *text & 255;
		px = (c % 16) * 16;
		py = (c / 16) * 16;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_BlitSurface(charset, &s, screen, &d);
		x += 16;
		text++;
	}
}

void MySDL::DrawString(char* text, Vector2d* position) {
	this->DrawString(text, position->GetX(), position->GetY());
}

float MySDL::DeltaTime() {
	return (newTime - oldTime) / 1000.f;
}

void MySDL::UpdateScreen() {
	SDL_UpdateTexture(texture, NULL, screen->pixels, screen->pitch);
	
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void MySDL::UpdateTime() {
	oldTime = newTime;
	newTime = SDL_GetTicks();
}

MySDL::~MySDL() {
	//Zwolnienie charset-u
	this->CleanSprite(charset);

	//Zwolnienie okna
	SDL_DestroyWindow(window);
	window = NULL;

	//Zamkniecie SDL
	SDL_Quit();
}