#include "Engine.h"
int mapInput[18][19] = {
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },//1
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },//2
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },//3
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },//4
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },//5
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },//6
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },//7
{ 0,0,0,0,0,0,-1,0,0,0,0,0,0,0,0,0,0,0,0 },//8
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },//9
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,0 },//10
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },//11
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },//12
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },//13
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },//14
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },//15
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },//16
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },//17
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },//18
};

Engine::Engine(const char* x, int width, int height)
{
	w = width;
	h = height;

	//Initialize the SDL subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		cout << "Subsystems succesffully initialized." << endl;
		isRunning = true;
	}
	else
	{
		cout << "Failure to initialize subsystems." << endl;
		cout << SDL_GetError() << endl;
		isRunning = false;
	}

	//Create the window object
	mainWindow = SDL_CreateWindow(x, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, NULL);

	if (mainWindow != NULL)
	{
		cout << "Window created succesffully." << endl;
		isRunning = true;
	}
	else
	{
		cout << "Failure to create Window." << endl;
		cout << SDL_GetError() << endl;
		isRunning = false;
	}

	//Create the main rendering object
	mainRenderer = SDL_CreateRenderer(mainWindow, -1, 0);

	if (mainRenderer != NULL)
	{
		cout << "Main Rendering device created." << endl;
		isRunning = true;
	}
	else
	{
		cout << "Failure to initialize main rendering device" << endl;
		cout << SDL_GetError() << endl;
		isRunning = false;
	}

	//Load Background Texture
	mainSurface = IMG_Load("/Users/Dab908/Desktop/Xcode Projects/snakeGame/Assets/background.png");
	backgroundTexture = SDL_CreateTextureFromSurface(mainRenderer, mainSurface);
	SDL_FreeSurface(mainSurface);
	backgroundRect.h = 40;
	backgroundRect.w = 40;

	//Load Border
	mainSurface = IMG_Load("/Users/Dab908/Desktop/Xcode Projects/snakeGame/Assets/gameBorder.png");
	border = SDL_CreateTextureFromSurface(mainRenderer, mainSurface);
	SDL_FreeSurface(mainSurface);

	//Load ScoreBoard
	mainSurface = IMG_Load("/Users/Dab908/Desktop/Xcode Projects/snakeGame/Assets/SCORE.png");
	SCORE = SDL_CreateTextureFromSurface(mainRenderer, mainSurface);
	SDL_FreeSurface(mainSurface);

	//Load num Textures
	mainSurface = IMG_Load("/Users/Dab908/Desktop/Xcode Projects/snakeGame/Assets/pyxel_NUM.png");
	num1 = SDL_CreateTextureFromSurface(mainRenderer, mainSurface);
	num2 = SDL_CreateTextureFromSurface(mainRenderer, mainSurface);
	num3 = SDL_CreateTextureFromSurface(mainRenderer, mainSurface);
	SDL_FreeSurface(mainSurface);



	//Initialize num RECT
	numRect.h = 40;
	numRect.w = 40;
	numRect.x = 0;
	numRect.y = 0;

	//Instantiate the Fruit
	fruit = new GameObject(mainRenderer, mainSurface, "/Users/Dab908/Desktop/Xcode Projects/snakeGame/Assets/fruit.png",w,h);

	//Initialize the map

	this->loadMap(mapInput);

	//Initialize stop direction
	direction = 0;

	//Initialize snake size
	snakeParts = 3;

	//Initialize time dependant seed
	srand(time(NULL));
    
    //Instantiate the Player
    player = new Snake(mainRenderer, mainSurface, width, height, &isRunning);
    
    //Initialize Engine Thread
    _engineTHR = new std::thread(&Engine::Update, this);

}

void Engine::Render()
{
	SDL_RenderClear(mainRenderer);
	for (int row = 0;row < 18;row++)
	{
		for (int col = 0;col < 19;col++)
		{
			backgroundRect.x = col * 40;
			backgroundRect.y = row * 40;
			SDL_RenderCopy(mainRenderer, backgroundTexture, NULL, &backgroundRect);

		}
	}
	backgroundRect.x = 19 * 40;
	for (int row = 0;row < 18;row++)
	{
		backgroundRect.y = row * 40;
		SDL_RenderCopy(mainRenderer, border, NULL, &backgroundRect);
	}
	backgroundRect.x = 20 * 40;
	backgroundRect.y = 2 * 40;
	backgroundRect.w = 40 * 6;
	SDL_RenderCopy(mainRenderer, SCORE, NULL, &backgroundRect);
	if (Score < 10)
	{
		numRect.x = 40 * Score;
		backgroundRect.x = 23 * 40;
		backgroundRect.y = 4 * 40;
		backgroundRect.w = 40;
		SDL_RenderCopy(mainRenderer, num1, &numRect, &backgroundRect);
	}
	else if (Score < 100)
	{
		numRect.x = 40 * (Score % 10);
		backgroundRect.x = 23 * 40;
		backgroundRect.y = 4 * 40;
		backgroundRect.w = 40;
		SDL_RenderCopy(mainRenderer, num1, &numRect, &backgroundRect);
		numRect.x = 40 * (Score / 10);
		backgroundRect.x = 22 * 40;
		SDL_RenderCopy(mainRenderer, num1, &numRect, &backgroundRect);
	}
	player->snakeRender(mainRenderer,map);
	fruit->objectRender(mainRenderer,map);
	SDL_RenderPresent(mainRenderer);
}

void Engine::setNumRect()
{

}

bool Engine::Running()
{
	return isRunning;
}

void Engine::clean()
{
	SDL_DestroyWindow(mainWindow);
	SDL_DestroyRenderer(mainRenderer);
	SDL_Quit();
}

void Engine::Update()
{
    while (isRunning)
    {
        int frametime;
        //FPS limit
        const int FPS = 8;
        const int frameDelay = 1000 / FPS;
        Uint32 framestart;
        framestart = SDL_GetTicks();
        updateMap();
        frametime = SDL_GetTicks() - framestart;
        
        if (frameDelay > frametime)
        {
            SDL_Delay(frameDelay - frametime);
        }
    }
}

void Engine::EventManager()
{
    SDL_PollEvent(&shared::event);
	switch (shared::event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

SDL_Renderer* Engine::getRenderer()
{
	return mainRenderer;
}

SDL_Surface* Engine::getSurface()
{
	return mainSurface;
}

SDL_Window* Engine::getWindow()
{
	return mainWindow;
}

void Engine::updateMap()
{
	for (int cnt = 1;cnt <= snakeParts;cnt++)
	{
		for (int row = 0;row < 18;row++)
		{
			for (int col = 0;col < 19;col++)
			{
				if (map[row][col] == cnt)
				{
					if (player->direction == 0)
					{
						//Do nothing
					}
					else if(player->direction == 1)
					{
						//Move Up
						if (row == 0)
						{
							//Hit upper wall
							//Game Over
							player->direction = 0;
							isRunning = false;
						}
						else if (map[row-1][col] == 0)
						{
							//Empty tile
							if (cnt == 1)
							{
								pastX1 = row;
								pastY1 = col;
								map[row - 1][col] = cnt;
								map[row][col] = 0;
							}
							else if(cnt>1)
							{
								pastX2 = row;
								pastY2 = col;

								map[row][col] = 0;
								map[pastX1][pastY1] = cnt;
								
								pastX1 = pastX2;
								pastY1 = pastY2;
							}
						}
						else if (map[row-1][col] == -1)
						{
							//eat a fruit
							if (cnt == 1)
							{
								pastX1 = row;
								pastY1 = col;
								map[row - 1][col] = cnt;
								map[row][col] = -1;
								//Generate random position for new fruit
								pastX2 = rand() % 18;
								pastY2 = rand() % 19;
								while (map[pastX2][pastY2] != 0)
								{
									srand(time(NULL));
									pastX2 = rand() % 18;
									pastY2 = rand() % 19;
								}
								map[pastX2][pastY2] = -1;
								Score++;
							}
							else if (cnt > 1)
							{
								if (cnt == snakeParts)
								{
									map[pastX1][pastY1] = cnt;
									map[row][col] = ++snakeParts;
									pastX1 = row;
									pastY1 = col;
								}
								else
								{
									map[row][col] = -1;
									map[pastX1][pastY1] = cnt;
									pastX1 = row;
									pastY1 = col;
								}
							}

						}
						else if (map[row-1][col] > 1)
						{
							//Hit body part
						}
					}
					else if (player->direction == 2)
					{
						//Move left
						if (col == 0)
						{
							//Hit left wall
							//Game Over
							player->direction = 0;
							isRunning = false;
						}
						else if (map[row][col-1] == 0)
						{
							//Empty tile
							if (cnt == 1)
							{
								pastX1 = row;
								pastY1 = col;
								map[row][col-1] = cnt;
								map[row][col] = 0;
							}
							else
							{
								pastX2 = row;
								pastY2 = col;

								map[row][col] = 0;
								map[pastX1][pastY1] = cnt;

								pastX1 = pastX2;
								pastY1 = pastY2;
							}
						}
						else if (map[row][col - 1] == -1)
						{
							//eat a fruit
							if (cnt == 1)
							{
								pastX1 = row;
								pastY1 = col;
								map[row][col-1] = cnt;
								map[row][col] = -1;
								//Generate random position for new fruit
								pastX2 = rand() % 18;
								pastY2 = rand() % 19;
								while (map[pastX2][pastY2] != 0)
								{
									srand(time(NULL));
									pastX2 = rand() % 18;
									pastY2 = rand() % 19;
								}
								map[pastX2][pastY2] = -1;
								Score++;
							}
							else if (cnt > 1)
							{
								if (cnt == snakeParts)
								{
									map[pastX1][pastY1] = cnt;
									map[row][col] = ++snakeParts;
									pastX1 = row;
									pastY1 = col;
								}
								else
								{
									map[row][col] = -1;
									map[pastX1][pastY1] = cnt;
									pastX1 = row;
									pastY1 = col;
								}
							}
						}
						else if (map[row][col - 1] > 1)
						{
							//Hit body part
						}
					}
					else if (player->direction == 3)
					{
						//Move down

						if (row == 17)
						{
							direction = 0;
							isRunning = false;
						}

						if (row != 17 && map[row + 1][col] == 0)
						{
							if (cnt == 1)
							{
								
								pastX1 = row;
								pastY1 = col;
								map[row + 1][col] = cnt;
								map[row][col] = 0;
							}
							else
							{
								map[pastX1][pastY1] = cnt;
								pastX1 = row;
								pastY1 = col;
								map[row][col] = 0;

							}
						}
						else if (map[row + 1][col] == -1)
						{
							//eat a fruit
							if (cnt == 1)
							{
								pastX1 = row;
								pastY1 = col;
								map[row + 1][col] = cnt;
								map[row][col] = -1;
								//Generate random position for new fruit
								pastX2 = rand() % 18;
								pastY2 = rand() % 19;
								while (map[pastX2][pastY2] != 0)
								{
									srand(time(NULL));
									pastX2 = rand() % 18;
									pastY2 = rand() % 19;
								}
								map[pastX2][pastY2] = -1;
								Score++;
							}
							else if (cnt > 1)
							{
								if (cnt == snakeParts)
								{
									map[pastX1][pastY1] = cnt;
									map[row][col] = ++snakeParts;
									pastX1 = row;
									pastY1 = col;
								}
								else
								{
									map[row][col] = -1;
									map[pastX1][pastY1] = cnt;
									pastX1 = row;
									pastY1 = col;
								}
							}

						}
					}
					else if (player->direction == 4)
					{
						//Move right
						if (col == 18)
						{
							//Hit left wall
							//Game Over
							player->direction = 0;
							isRunning = false;
						}
						else if (map[row][col + 1] == 0)
						{
							//Empty tile
							if (cnt == 1)
							{
								pastX1 = row;
								pastY1 = col;
								map[row][col] = 0;
								map[row][col + 1] = cnt;
							}
							else
							{
								pastX2 = row;
								pastY2 = col;

								map[row][col] = 0;
								map[pastX1][pastY1] = cnt;

								pastX1 = pastX2;
								pastY1 = pastY2;
							}
						}
						else if (map[row][col + 1] == -1)
						{
							//eat a fruit
							if (cnt == 1)
							{
								pastX1 = row;
								pastY1 = col;
								map[row][col+1] = cnt;
								map[row][col] = -1;
								//Generate random position for new fruit
								pastX2 = rand() % 18;
								pastY2 = rand() % 19;
								while (map[pastX2][pastY2] != 0)
								{
									srand(time(NULL));
									pastX2 = rand() % 18;
									pastY2 = rand() % 19;
								}
								map[pastX2][pastY2] = -1;
								Score++;
							}
							else if (cnt > 1)
							{
								if (cnt == snakeParts)
								{
									map[pastX1][pastY1] = cnt;
									map[row][col] = ++snakeParts;
									pastX1 = row;
									pastY1 = col;

								}
								else
								{
									map[row][col] = -1;
									map[pastX1][pastY1] = cnt;
									pastX1 = row;
									pastY1 = col;
								}
							}
						}
						else if (map[row][col + 1] > 1)
						{
							//Hit body part
						}
					}
					row = 19;
					col = 19;
				}
			}
		}
	}
}

void Engine::loadMap(int arr[18][19])
{
	for (int row = 0;row < 18;row++)
	{
		for (int col = 0;col < 19;col++)
		{
			map[row][col] = arr[row][col];
		}
	}
}

Engine::~Engine()
{
}
