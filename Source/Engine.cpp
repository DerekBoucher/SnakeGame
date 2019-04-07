#include "Engine.h"
int mapInput[ARENA_SIZE_ROW][ARENA_SIZE_COL] = {
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
	backgroundRect.h = TILE_SIZE;
	backgroundRect.w = TILE_SIZE;

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
	numRect.h = TILE_SIZE;
	numRect.w = TILE_SIZE;
	numRect.x = 0;
	numRect.y = 0;

	//Instantiate the Fruit
	fruit = new GameObject(mainRenderer, mainSurface, "/Users/Dab908/Desktop/Xcode Projects/snakeGame/Assets/fruit.png",w,h);

	//Initialize the map

	this->loadMap(mapInput);

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
	for (int row = 0;row < ARENA_SIZE_ROW;row++)
	{
		for (int col = 0;col < ARENA_SIZE_COL;col++)
		{
			backgroundRect.x = col * TILE_SIZE;
			backgroundRect.y = row * TILE_SIZE;
			SDL_RenderCopy(mainRenderer, backgroundTexture, NULL, &backgroundRect);

		}
	}
	backgroundRect.x = ARENA_SIZE_COL * TILE_SIZE;
	for (int row = 0;row < ARENA_SIZE_ROW;row++)
	{
		backgroundRect.y = row * TILE_SIZE;
		SDL_RenderCopy(mainRenderer, border, NULL, &backgroundRect);
	}
	backgroundRect.x = 20 * TILE_SIZE;
	backgroundRect.y = 2 * TILE_SIZE;
	backgroundRect.w = TILE_SIZE * 6;
	SDL_RenderCopy(mainRenderer, SCORE, NULL, &backgroundRect);
	if (Score < 10)
	{
		numRect.x = TILE_SIZE * Score;
		backgroundRect.x = 23 * TILE_SIZE;
		backgroundRect.y = 4 * TILE_SIZE;
		backgroundRect.w = TILE_SIZE;
		SDL_RenderCopy(mainRenderer, num1, &numRect, &backgroundRect);
	}
	else if (Score < 100)
	{
		numRect.x = TILE_SIZE * (Score % 10);
		backgroundRect.x = 23 * TILE_SIZE;
		backgroundRect.y = 4 * TILE_SIZE;
		backgroundRect.w = TILE_SIZE;
		SDL_RenderCopy(mainRenderer, num1, &numRect, &backgroundRect);
		numRect.x = TILE_SIZE * (Score / 10);
		backgroundRect.x = 22 * TILE_SIZE;
		SDL_RenderCopy(mainRenderer, num1, &numRect, &backgroundRect);
	}
	player->snakeRender(mainRenderer,map);
	fruit->objectRender(mainRenderer,map);
	SDL_RenderPresent(mainRenderer);
}

bool Engine::Running()
{
	return isRunning;
}

void Engine::clean()
{
	SDL_DestroyWindow(mainWindow);
	SDL_DestroyRenderer(mainRenderer);
    SDL_DestroyTexture(num1);
    SDL_DestroyTexture(num2);
    SDL_DestroyTexture(num3);
    SDL_DestroyTexture(border);
    SDL_DestroyTexture(SCORE);
    SDL_DestroyTexture(backgroundTexture);
    delete fruit;
	SDL_Quit();
}

void Engine::Update()
{
    while (isRunning)
    {
        int frametime;
        const int FPS = 8;
        const int frameDelay = 1000 / FPS;
        Uint32 framestart;
        framestart = SDL_GetTicks();
        updateMap();
        Render();
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
    int pastRow = 0;
    int pastCol = 0;
    switch(player->direction)
    {
        case MOVE_UP:
        {
            //Eat Fruit
            if(map[HEAD_ROW-1][HEAD_COL] == -1)
            {
                //Increment Score
                ++Score;
                
                //Increment SnakeParts
                ++snakeParts;
                
                //Move head
                map[HEAD_ROW-1][HEAD_COL] = SNAKE_HEAD;
                map[HEAD_ROW][HEAD_COL] = 0;
                pastRow = HEAD_ROW;
                pastCol = HEAD_COL;
                HEAD_ROW = HEAD_ROW-1;
                HEAD_COL = HEAD_COL;
                
                //Generate new random fruit
                int row = rand()%ARENA_SIZE_ROW;
                int col = rand()%ARENA_SIZE_COL;
                while(map[row][col] != 0)
                {
                    row = rand()%ARENA_SIZE_ROW;
                    col = rand()%ARENA_SIZE_COL;
                }
                map[row][col] = -1;
                
                for(int i = 2; i <= snakeParts; ++i)
                    for(int j = 0; j < ARENA_SIZE_ROW; ++j)
                        for(int k = 0; k < ARENA_SIZE_COL; ++k)
                        {
                            if(map[j][k] == i)
                            {
                                map[pastRow][pastCol] = i;
                                map[j][k] = 0;
                                pastRow = j;
                                pastCol = k;
                                j = ARENA_SIZE_ROW;
                                k = ARENA_SIZE_COL;
                            }
                            if(i == snakeParts)
                            {
                                map[pastRow][pastCol] = i;
                            }
                        }
                
            }
            //Collide with other snake part OR top wall
            else if(map[HEAD_ROW-1][HEAD_COL] > 0
                    || HEAD_ROW - 1 < 0)
            {
                //Game Over
                isRunning = false;
                player->direction = 0;
            }
            else
            {
                //Move head
                map[HEAD_ROW-1][HEAD_COL] = SNAKE_HEAD;
                map[HEAD_ROW][HEAD_COL] = 0;
                pastRow = HEAD_ROW;
                pastCol = HEAD_COL;
                HEAD_ROW = HEAD_ROW-1;
                HEAD_COL = HEAD_COL;
                
                for(int i = 2; i <= snakeParts; ++i)
                    for(int j = 0; j < ARENA_SIZE_ROW; ++j)
                        for(int k = 0; k < ARENA_SIZE_COL; ++k)
                        {
                            if(map[j][k] == i)
                            {
                                map[pastRow][pastCol] = i;
                                map[j][k] = 0;
                                pastRow = j;
                                pastCol = k;
                                j = ARENA_SIZE_ROW;
                                k = ARENA_SIZE_COL;
                            }
                        }
            }
            break;
        }
        case MOVE_RIGHT:
        {
            //Eat Fruit
            if(map[HEAD_ROW][HEAD_COL+1] == -1)
            {
                //Increment Score
                ++Score;
                
                //Increment SnakeParts
                ++snakeParts;
                
                //Move head
                map[HEAD_ROW][HEAD_COL+1] = SNAKE_HEAD;
                map[HEAD_ROW][HEAD_COL] = 0;
                pastRow = HEAD_ROW;
                pastCol = HEAD_COL;
                HEAD_ROW = HEAD_ROW;
                HEAD_COL = HEAD_COL+1;
                
                //Generate new random fruit
                int row = rand()%ARENA_SIZE_ROW;
                int col = rand()%ARENA_SIZE_COL;
                while(map[row][col] != 0)
                {
                    row = rand()%ARENA_SIZE_ROW;
                    col = rand()%ARENA_SIZE_COL;
                }
                map[row][col] = -1;
                
                for(int i = 2; i <= snakeParts; ++i)
                    for(int j = 0; j < ARENA_SIZE_ROW; ++j)
                        for(int k = 0; k < ARENA_SIZE_COL; ++k)
                        {
                            if(map[j][k] == i)
                            {
                                map[pastRow][pastCol] = i;
                                map[j][k] = 0;
                                pastRow = j;
                                pastCol = k;
                                j = ARENA_SIZE_ROW;
                                k = ARENA_SIZE_COL;
                            }
                            if(i == snakeParts)
                            {
                                map[pastRow][pastCol] = i;
                            }
                        }
                
            }
            //Collide with other snake part OR Right wall
            else if(map[HEAD_ROW][HEAD_COL+1] > 0
                    || HEAD_COL + 1 > ARENA_SIZE_COL-1)
            {
                //Game Over
                isRunning = false;
                player->direction = 0;
            }
            else
            {
                //Move head
                map[HEAD_ROW][HEAD_COL+1] = SNAKE_HEAD;
                map[HEAD_ROW][HEAD_COL] = 0;
                pastRow = HEAD_ROW;
                pastCol = HEAD_COL;
                HEAD_ROW = HEAD_ROW;
                HEAD_COL = HEAD_COL+1;
                
                for(int i = 2; i <= snakeParts; ++i)
                    for(int j = 0; j < ARENA_SIZE_ROW; ++j)
                        for(int k = 0; k < ARENA_SIZE_COL; ++k)
                {
                    if(map[j][k] == i)
                    {
                        map[pastRow][pastCol] = i;
                        map[j][k] = 0;
                        pastRow = j;
                        pastCol = k;
                        j = ARENA_SIZE_ROW;
                        k = ARENA_SIZE_COL;
                    }
                }
            }
            break;
        }
        case MOVE_DOWN:
        {
            //Eat Fruit
            if(map[HEAD_ROW+1][HEAD_COL] == -1)
            {
                //Increment Score
                ++Score;
                
                //Increment SnakeParts
                ++snakeParts;
                
                //Move head
                map[HEAD_ROW+1][HEAD_COL] = SNAKE_HEAD;
                map[HEAD_ROW][HEAD_COL] = 0;
                pastRow = HEAD_ROW;
                pastCol = HEAD_COL;
                HEAD_ROW = HEAD_ROW+1;
                HEAD_COL = HEAD_COL;
                
                //Generate new random fruit
                int row = rand()%ARENA_SIZE_ROW;
                int col = rand()%ARENA_SIZE_COL;
                while(map[row][col] != 0)
                {
                    row = rand()%ARENA_SIZE_ROW;
                    col = rand()%ARENA_SIZE_COL;
                }
                map[row][col] = -1;
                
                for(int i = 2; i <= snakeParts; ++i)
                    for(int j = 0; j < ARENA_SIZE_ROW; ++j)
                        for(int k = 0; k < ARENA_SIZE_COL; ++k)
                        {
                            if(map[j][k] == i)
                            {
                                map[pastRow][pastCol] = i;
                                map[j][k] = 0;
                                pastRow = j;
                                pastCol = k;
                                j = ARENA_SIZE_ROW;
                                k = ARENA_SIZE_COL;
                            }
                            if(i == snakeParts)
                            {
                                map[pastRow][pastCol] = i;
                            }
                        }
                
            }
            //Collide with other snake part OR Right wall
            else if(map[HEAD_ROW+1][HEAD_COL] > 0
                    || HEAD_ROW + 1 > ARENA_SIZE_ROW-1)
            {
                //Game Over
                isRunning = false;
                player->direction = 0;
            }
            else
            {
                //Move head
                map[HEAD_ROW+1][HEAD_COL] = SNAKE_HEAD;
                map[HEAD_ROW][HEAD_COL] = 0;
                pastRow = HEAD_ROW;
                pastCol = HEAD_COL;
                HEAD_ROW = HEAD_ROW+1;
                HEAD_COL = HEAD_COL;

                for(int i = 2; i <= snakeParts; ++i)
                    for(int j = 0; j < ARENA_SIZE_ROW; ++j)
                        for(int k = 0; k < ARENA_SIZE_COL; ++k)
                        {
                            if(map[j][k] == i)
                            {
                                map[pastRow][pastCol] = i;
                                map[j][k] = 0;
                                pastRow = j;
                                pastCol = k;
                                j = ARENA_SIZE_ROW;
                                k = ARENA_SIZE_COL;
                            }
                        }
            }
            break;
        }
        case MOVE_LEFT:
        {
            //Eat Fruit
            if(map[HEAD_ROW][HEAD_COL-1] == -1)
            {
                //Increment Score
                ++Score;
                
                //Increment SnakeParts
                ++snakeParts;
                
                //Move head
                map[HEAD_ROW][HEAD_COL-1] = SNAKE_HEAD;
                map[HEAD_ROW][HEAD_COL] = 0;
                pastRow = HEAD_ROW;
                pastCol = HEAD_COL;
                HEAD_ROW = HEAD_ROW;
                HEAD_COL = HEAD_COL-1;
                
                //Generate new random fruit
                int row = rand()%ARENA_SIZE_ROW;
                int col = rand()%ARENA_SIZE_COL;
                while(map[row][col] != 0)
                {
                    row = rand()%ARENA_SIZE_ROW;
                    col = rand()%ARENA_SIZE_COL;
                }
                map[row][col] = -1;
                
                for(int i = 2; i <= snakeParts; ++i)
                    for(int j = 0; j < ARENA_SIZE_ROW; ++j)
                        for(int k = 0; k < ARENA_SIZE_COL; ++k)
                        {
                            if(map[j][k] == i)
                            {
                                map[pastRow][pastCol] = i;
                                map[j][k] = 0;
                                pastRow = j;
                                pastCol = k;
                                j = ARENA_SIZE_ROW;
                                k = ARENA_SIZE_COL;
                            }
                            if(i == snakeParts)
                            {
                                map[pastRow][pastCol] = i;
                            }
                        }
                
            }
            //Collide with other snake part OR Right wall
            else if(map[HEAD_ROW][HEAD_COL-1] > 0
                    || HEAD_COL - 1 < 0)
            {
                //Game Over
                isRunning = false;
                player->direction = 0;
            }
            else
            {
                //Move head
                map[HEAD_ROW][HEAD_COL-1] = SNAKE_HEAD;
                map[HEAD_ROW][HEAD_COL] = 0;
                pastRow = HEAD_ROW;
                pastCol = HEAD_COL;
                HEAD_ROW = HEAD_ROW;
                HEAD_COL = HEAD_COL-1;
                
                for(int i = 2; i <= snakeParts; ++i)
                    for(int j = 0; j < ARENA_SIZE_ROW; ++j)
                        for(int k = 0; k < ARENA_SIZE_COL; ++k)
                        {
                            if(map[j][k] == i)
                            {
                                map[pastRow][pastCol] = i;
                                map[j][k] = 0;
                                pastRow = j;
                                pastCol = k;
                                j = ARENA_SIZE_ROW;
                                k = ARENA_SIZE_COL;
                            }
                        }
            }
            break;
        }
    }
}

void Engine::loadMap(int arr[ARENA_SIZE_ROW][ARENA_SIZE_COL])
{
	for (int row = 0;row < ARENA_SIZE_ROW;row++)
	{
		for (int col = 0;col < ARENA_SIZE_COL;col++)
		{
			map[row][col] = arr[row][col];
		}
	}
}

Engine::~Engine()
{
}
