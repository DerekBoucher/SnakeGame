#ifndef _ENGINE_H_
#define _ENGINE_H_
#pragma once
#include <math.h>
#include <ctime>
#include <thread>
#include <iostream>

#include "SDL.h"
#include "SDL_image.h"
#include "Snake.h"
#include "GameObject.h"
#include "Shared.h"

#define HEAD_ROW player->snakeHeadRow
#define HEAD_COL player->snakeHeadCol
#define SNAKE_HEAD 1

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

	//Clean the subsystems if Application closes
	void clean();

	//Handle any type of application event
	void EventManager();

	//Check if game is still operating
	bool Running();

	//tilemap update function
	void updateMap();
	void loadMap(int[ARENA_SIZE_ROW][ARENA_SIZE_COL]);

	//Return functions for other classes
	SDL_Renderer* getRenderer();
	SDL_Surface* getSurface();
	SDL_Window* getWindow();
    Snake * player;

private:

	int w;
	int h;

	bool backgroundRenderOK;

	//Map
	int map[ARENA_SIZE_ROW][ARENA_SIZE_COL];

	//Snake part count
	int snakeParts;

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
	GameObject * fruit;
    std::thread* _engineTHR;


};

#endif /* _ENGINE_H_ */
