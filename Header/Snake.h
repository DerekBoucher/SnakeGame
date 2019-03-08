#pragma once
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <iostream>
#include <thread>
#include "Shared.h"



class Snake
{
public:

	//Snake Constructor that initializes the snake textures for the head and body tiles
	Snake(SDL_Renderer*,SDL_Surface*,int,int,bool*);

	//Main rendering function for the snake object
	bool snakeRender(SDL_Renderer*, int[18][19]);

	//User control logic to move snake
	void userInput();



	~Snake();
    
    //SnakeDirection
    int direction;

    bool* isRunning;
private:
	//Texture components
	SDL_Texture* headTexture;
	SDL_Texture* bodyTexture;
    
	//Rect
	SDL_Rect destRect;

	SDL_Event userrInput;
    
    
    
};

