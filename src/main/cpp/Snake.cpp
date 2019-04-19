#include "Snake.h"
using namespace std;

SDL_Event shared::event;

Snake::Snake(SDL_Renderer* passedRenderer, SDL_Surface* passedSurface, int xCoord, int yCoord, bool* running)
{
	//Format the dimensions of the destination rectangle
	destRect.h = TILE_SIZE;
	destRect.w = TILE_SIZE;

	//Load texture for head
	passedSurface = IMG_Load("Assets/SnakeHead.png");
	headTexture = SDL_CreateTextureFromSurface(passedRenderer, passedSurface);
	SDL_FreeSurface(passedSurface);

	//Load Texture for body
	passedSurface = IMG_Load("Assets/snakeBody.png");
	bodyTexture = SDL_CreateTextureFromSurface(passedRenderer, passedSurface);
	SDL_FreeSurface(passedSurface);

	//Instantiate direction to 0 = game hasnt started yet
	direction = 0;
    
    isRunning = running;
    
    snakeHeadRow = 9;
    snakeHeadCol = 15;
    
}

bool Snake::snakeRender(SDL_Renderer* passedRenderer,int arr[ARENA_SIZE_ROW][ARENA_SIZE_COL])
{
	//Render every snake part to the screen
	for (int row = 0;row < ARENA_SIZE_ROW;row++)
	{
		for (int col = 0;col < ARENA_SIZE_COL;col++)
		{
			if (arr[row][col] == 1)
			{
				//Render the snake head
				destRect.x = col * TILE_SIZE;
				destRect.y = row * TILE_SIZE;
				SDL_RenderCopy(passedRenderer, headTexture, NULL, &destRect);
			}
			else if(arr[row][col] > 1)
			{
				destRect.x = col * TILE_SIZE;
				destRect.y = row * TILE_SIZE;
				SDL_RenderCopy(passedRenderer, bodyTexture, NULL, &destRect);
			}
		}
	}
	return true;
}

void Snake::userInput()
{
    SDL_PollEvent(&shared::event);
	switch (shared::event.type)
	{
	case SDL_KEYDOWN:
		switch (shared::event.key.keysym.sym)
		{
		case SDLK_w:
			if (direction != MOVE_DOWN)
			{
				direction = MOVE_UP;
			}
			break;
		case SDLK_a:
			if (direction != MOVE_RIGHT)
			{
				direction = MOVE_LEFT;
			}
			break;
		case SDLK_s:
			if (direction != MOVE_UP)
			{
				direction = MOVE_DOWN;
			}
			break;
		case SDLK_d:
			if (direction != MOVE_LEFT)
			{
				direction = MOVE_RIGHT;
			}
			break;
		case SDLK_CLEAR:
			direction = 0;
			break;
		default:
			break;
		}
		break;
        case SDL_QUIT:
            *isRunning = false;
            break;
	default:
		break;
	}
}

Snake::~Snake()
{
}
