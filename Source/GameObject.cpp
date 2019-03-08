#include "GameObject.h"


GameObject::GameObject(SDL_Renderer* passedRenderer, SDL_Surface* passedSurface, const char* file, int xCoord, int yCoord)
{
	//Load Texture of GameObject
	passedSurface = IMG_Load(file);
	objectTexture = SDL_CreateTextureFromSurface(passedRenderer, passedSurface);
	SDL_FreeSurface(passedSurface);

	//Set the Texture size to be rendered
	objectLocation.h = 40;
	objectLocation.w = 40;
}

SDL_Rect GameObject::generateRandomRect(std::vector<SDL_Rect> passedSnakeParts, int xCoord, int yCoord)
{
	//Boolean to determine if coordinate is not occupied
	bool isOccupied = true;
	int j = 0;

	//Generate a random position on the screen
	while (isOccupied)
	{
		int x = 40 * 10;
		int y = 40 * 12;
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

void GameObject::objectRender(SDL_Renderer* passedRenderer, int arr[18][19])
{
	for (int i = 0;i < 18;i++)
	{
		for (int j = 0;j < 19;j++)
		{
			if (arr[i][j] == -1)
			{
				objectLocation.x = j * 40;
				objectLocation.y = i * 40;
				SDL_RenderCopy(passedRenderer, objectTexture, NULL, &objectLocation);
			}
		}
	}
}

GameObject::~GameObject()
{
}
