#include "GameObject.h"


GameObject::GameObject(SDL_Renderer* passedRenderer, SDL_Surface* passedSurface, const char* file, int xCoord, int yCoord)
{
	//Load Texture of GameObject
	passedSurface = IMG_Load(file);
	objectTexture = SDL_CreateTextureFromSurface(passedRenderer, passedSurface);
	SDL_FreeSurface(passedSurface);

	//Set the Texture size to be rendered
	objectLocation.h = TILE_SIZE;
	objectLocation.w = TILE_SIZE;
}

SDL_Rect GameObject::generateRandomRect(std::vector<SDL_Rect> passedSnakeParts, int xCoord, int yCoord)
{
	//Boolean to determine if coordinate is not occupied
	bool isOccupied = true;
	int j = 0;

	//Generate a random position on the screen
	while (isOccupied)
	{
		int x = TILE_SIZE * 10;
		int y = TILE_SIZE * 12;
		objectLocation.x = x;
		objectLocation.y = y;
		//Verify if any of the snakeparts already occupy generated position
		for (std::vector<SDL_Rect>::iterator i = passedSnakeParts.begin();i < passedSnakeParts.end();i++)
		{
			if (objectLocation.x == passedSnakeParts[j].x && objectLocation.y == passedSnakeParts[j].y)
			{
				isOccupied = true;
				i = passedSnakeParts.end();
				break;
			}
			else
			{
				j++;
				isOccupied = false;
			}
		}
	}
	return objectLocation;
}

void GameObject::objectRender(SDL_Renderer* passedRenderer, int arr[ARENA_SIZE_ROW][ARENA_SIZE_COL])
{
	for (int i = 0;i < ARENA_SIZE_ROW;i++)
	{
		for (int j = 0;j < ARENA_SIZE_COL;j++)
		{
			if (arr[i][j] == -1)
			{
				objectLocation.x = j * TILE_SIZE;
				objectLocation.y = i * TILE_SIZE;
				SDL_RenderCopy(passedRenderer, objectTexture, NULL, &objectLocation);
			}
		}
	}
}

GameObject::~GameObject()
{
    SDL_DestroyTexture(objectTexture);
}
