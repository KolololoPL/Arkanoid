#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Highscores.h"
#include "Config.h"

Highscores* Highscores::current = nullptr;

Highscores::Highscores(char* path) {
	Highscores::current = this;
	
	this->path = path;
	this->position = Vector2d((SCREEN_WIDTH - HIGHSCORES_WIDTH) / 2, SCREEN_HEIGHT / 2 + 100);
	for (int x = 0; x < 5; x++) {
		scores[x][0] = new char[24];
		scores[x][1] = new char[5];
	}
	nick[0] = '\0';

	FILE* file = fopen(path, "rb");
	if (file == NULL) {
		perror(path);
	} else {
		char line[30];
		line[0] = '\0';

		int c = fgetc(file), i = 0;
		while (c != EOF) {
			if (c == ':' && i < 5) {
				strcpy(scores[i][0], line);
				line[0] = '\0';
			} else if (c == '/' && i < 5) {
				strcpy(scores[i][1], line);
				line[0] = '\0';
				i++;
			} else if (c != '\n' && c != '\r') {
				int length = strlen(line);
				line[length] = c;
				line[length + 1] = '\0';
			}

			c = fgetc(file);
		}

		for (int x = i; x < 5; x++) {
			scores[x][0][0] = '\0';
			scores[x][1][0] = '\0';
		}

		fclose(file);
	}
}

void Highscores::Draw() {
	if (isKeyboardLocked) {
		MySDL::current->DrawString("Masz najlepszy wynik! Podaj nick:", &position);
		MySDL::current->DrawString("(Duze i male litery + cyfry)", &(position + Directions::down * 16));
		
		char line[35];
		if (shift)
			strcpy(line, "[ABC] -> ");
		else
			strcpy(line, "[abc] -> ");
		strcat(line, nick);

		MySDL::current->DrawString(line, &(position + Directions::down * 16 * 2.5f));
	} else {
		MySDL::current->DrawString("######### HIGHSCORES #########", &position);

		int i = 0;
		while (i < 5 && strlen(scores[i][0]) > 0) {
			char line[HIGHSCORES_WIDTH / 16 + 1];

			line[0] = '1' + i;
			line[1] = '\0';

			strcat(line, ") ");
			strcat(line, scores[i][0]);
			const int stop = HIGHSCORES_WIDTH / 16 - strlen(scores[i][1]);
			for (int x = strlen(line); x < stop; x++)
				line[x] = '.';
			line[stop] = '\0';
			strcat(line, scores[i][1]);

			MySDL::current->DrawString(line, &(position + Directions::down * 16 * (i + 1)));
			i++;
		}
	}
}

void Highscores::CheckIfHighScore(int score) {
	//Sprawdza czy pad³ rekord i jeœli tak, to odpowiednio aktualizuje scores
	for (int x = 0; x < 5; x++) {
		int min = atoi(scores[x][1]);
		if (strlen(scores[x][0]) == 0 || score > min) {
			for (int y = 3; y >= x; y--) {
				strcpy(scores[y + 1][0], scores[y][0]);
				strcpy(scores[y + 1][1], scores[y][1]);
			}

			//Wpisanie nowego rekordu
			scores[x][0][0] = '\0';
			sprintf(scores[x][1], "%d", score);

			nhIndex = x;
			isKeyboardLocked = true;
			return;
		}
	}
}

void Highscores::Save() {
	FILE* file = fopen(path, "wb");
	if (file == NULL) {
		perror(path);
	} else {
		int i = 0;
		while (i < 5 && strlen(scores[i][0]) > 0) {
			char line[35];
			
			strcpy(line, scores[i][0]);
			strcat(line, ":");
			strcat(line, scores[i][1]);
			strcat(line, "/");

			int length = strlen(line);
			line[length] = '\n';
			line[length + 1] = '\0';

			fputs(line, file);
			i++;
		}

		fclose(file);
	}
}

bool Highscores::IsKeyboardLocked() {
	return isKeyboardLocked;
}

void Highscores::OnKeydownEvent(SDL_Keycode key) {
	if (key == SDLK_RETURN && strlen(nick) > 0) {
		strcpy(scores[nhIndex][0], nick);
		nick[0] = '\0';
		
		this->Save();
		isKeyboardLocked = false;
	} else if (key == SDLK_BACKSPACE) {
		int length = strlen(nick);
		if (length > 0)
			nick[length - 1] = '\0';
	} else if (key == SDLK_LSHIFT || key == SDLK_RSHIFT) {
		shift = !shift;
	} else if (key >= 'a' && key <= 'z' && strlen(nick) < 23) {
		if (shift)
			key -= 32;

		int length = strlen(nick);
		nick[length] = key;
		nick[length + 1] = '\0';
	} else if (key >= '0' && key <= '9' && strlen(nick) < 23) {
		int length = strlen(nick);
		nick[length] = key;
		nick[length + 1] = '\0';
	}
}

Highscores::~Highscores() {
	
}
