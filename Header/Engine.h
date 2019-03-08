#pragma once
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <iostream>
#include "Snake.h"
#include "GameObject.h"
#include <math.h>
#include <ctime>

using namespace std;


class Engine
{
public:

	//Constructor(s)/Destructor(s)
	Engine(const char*, int, int);
	virtual ~Engine();

	//SDL subsystems initializer

	//Game Update Function
	void Update();

	//Game Engine main Rendering function
	void Render();
	void setNumRect();

	//Clean the subsystems if Application closes
	void clean();

	//Handle any type of application event
	void EventManager();

	//Check if game is still operating
	bool Running();

	//tilemap update function
	void updateMap();
	void loadMap(int[18][19]);

	//Return functions for other classes
	SDL_Renderer* getRenderer();
	SDL_Surface* getSurface();
	SDL_Window* getWindow();


private:

	int w;
	int h;

	bool backgroundRenderOK;

	//Map
	int map[18][19];

	//Snake part count
	int snakeParts;

	//integer value representing the direction of the snake
	int direction;

	//Integer values to hold past positions of the snake parts
	int pastX1 = 0;
	int pastX2 = 0;
	int pastY1 = 0;
	int pastY2 = 0;

	//Integer value containing the score
	int Score = 0;

	bool isRunning;
	SDL_Window* mainWindow;
	SDL_Renderer* mainRenderer;
	SDL_Surface* mainSurface;
	SDL_Texture* backgroundTexture;
	SDL_Texture* border;
	SDL_Texture* SCORE;
	SDL_Texture* num1;
	SDL_Texture* num2;
	SDL_Texture* num3;
	SDL_Rect backgroundRect;
	SDL_Rect numRect;
	Snake * player;
	GameObject * fruit;


};

