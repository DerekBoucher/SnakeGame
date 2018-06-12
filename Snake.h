#pragma once
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>



class Snake
{
public:

	//Snake Constructor that initializes the snake textures for the head and body tiles
	Snake(SDL_Renderer*,SDL_Surface*,int,int);

	//Main rendering function for the snake object
	bool snakeRender(SDL_Renderer*, int[18][19]);

	//User control logic to move snake
	int userInput();



	~Snake();

private:
	//Texture components
	SDL_Texture* headTexture;
	SDL_Texture* bodyTexture;

	//SnakeDirection
	int direction;

	//Rect
	SDL_Rect destRect;

	SDL_Event userrInput;
};

