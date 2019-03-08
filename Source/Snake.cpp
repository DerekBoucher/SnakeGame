#include "Snake.h"
using namespace std;

Snake::Snake(SDL_Renderer* passedRenderer, SDL_Surface* passedSurface, int xCoord, int yCoord)
{
	//Format the dimensions of the destination rectangle
	destRect.h = 40;
	destRect.w = 40;

	//Load texture for head
	passedSurface = IMG_Load("Assets/sisi.png");
	headTexture = SDL_CreateTextureFromSurface(passedRenderer, passedSurface);
	SDL_FreeSurface(passedSurface);

	//Load Texture for body
	passedSurface = IMG_Load("Assets/snakeBody.png");
	bodyTexture = SDL_CreateTextureFromSurface(passedRenderer, passedSurface);
	SDL_FreeSurface(passedSurface);

	//Instantiate direction to 0 = game hasnt started yet
	direction = 0;
}

bool Snake::snakeRender(SDL_Renderer* passedRenderer,int arr[18][19])
{
	//Render every snake part to the screen
	for (int row = 0;row < 18;row++)
	{
		for (int col = 0;col < 19;col++)
		{
			if (arr[row][col] == 1)
			{
				//Render the snake head
				destRect.x = col * 40;
				destRect.y = row * 40;
				SDL_RenderCopy(passedRenderer, headTexture, NULL, &destRect);
			}
			else if(arr[row][col] > 1)
			{
				destRect.x = col * 40;
				destRect.y = row * 40;
				SDL_RenderCopy(passedRenderer, bodyTexture, NULL, &destRect);
			}
		}
	}
	return true;
}

int Snake::userInput()
{
	
	SDL_PollEvent(&userrInput);
	switch (userrInput.type)
	{
	case SDL_KEYDOWN:
		switch (userrInput.key.keysym.sym)
		{
		case SDLK_w:
			if (direction != 3)
			{
				direction = 1;
			}
			break;
		case SDLK_a:
			if (direction != 4)
			{
				direction = 2;
			}
			break;
		case SDLK_s:
			if (direction != 1)
			{
				direction = 3;
			}
			break;
		case SDLK_d:
			if (direction != 2)
			{
				direction = 4;
			}
			break;
		case SDLK_CLEAR:
			direction = 0;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	return direction;
}

Snake::~Snake()
{
}