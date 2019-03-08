
#include "Engine.h"
#include "Snake.h"
#include "GameObject.h"

Engine* game = NULL;
int gameWidth, gameHeight;
int cnt = 0;

int main(int argc, char* args[])
{
	//Screen Resolution
	gameWidth = 1080;
	gameHeight = 720;

	//FPS limit
	const int FPS = 8;
	const int frameDelay = 1000 / FPS;
	Uint32 framestart;
	int frametime;

	//Instantiate the game engine
	game = new Engine("SnakeGame", gameWidth, gameHeight);

	//Game Loop
	while (game->Running())
	{
		framestart = SDL_GetTicks();

		game->Update();
		game->EventManager();
		game->Render();

		frametime = SDL_GetTicks() - framestart;

		if (frameDelay > frametime)
		{
			SDL_Delay(frameDelay - frametime);
		}
	}

	game->clean();

	return 0;
}
