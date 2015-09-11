#include "MySDL.h"
#include "Arkanoid.h"
#include "EventHandler.h"
#include "CollisionHandler.h"
#include "BonusHandler.h"
#include "Config.h"


using namespace std;

int main(int argc, char *argv[]) {
	MySDL* mySDL = new MySDL(WINDOW_WIDTH, WINDOW_HEIGHT, "Piotr Januszewski (Nr albumu 155079)");
	
	EventHandler* eventHandler = new EventHandler();
	CollisionHandler* collisionHandler = new CollisionHandler();

	Arkanoid* arkanoid = new Arkanoid();

	while (arkanoid->IsRunning()) {
		mySDL->UpdateTime();

		eventHandler->HandleSDLEvents();

		arkanoid->Update();

		collisionHandler->HandleCollisions();

		arkanoid->Draw();
	}

	delete arkanoid;
	delete eventHandler;
	delete collisionHandler;
	delete mySDL;
	
	return 0;
}