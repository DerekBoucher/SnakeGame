
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

	//Instantiate the game engine
	game = new Engine("SnakeGame", gameWidth, gameHeight);

	//Game Loop
	while (game->Running())
	{
        game->player->userInput();
        game->Render();
	}

	game->clean();

	return 0;
}
