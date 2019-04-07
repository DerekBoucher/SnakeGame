
#include "Engine.h"
#include "Snake.h"
#include "GameObject.h"

Engine* game = NULL;
int gameWidth, gameHeight;

int main(int argc, char* args[])
{
	//Screen Resolution
	gameWidth = TILE_SIZE * ARENA_SIZE_COL + SCORE_BUFFER_SIZE;
	gameHeight = TILE_SIZE * ARENA_SIZE_ROW;

	//Instantiate the game engine
	game = new Engine("SnakeGame", gameWidth, gameHeight);

	//Game Loop
	while (game->Running())
	{
        game->player->userInput();
	}

	game->clean();

	return 0;
}
