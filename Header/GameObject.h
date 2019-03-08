#pragma once
#include <math.h>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
using namespace std;

class GameObject
{
public:
	GameObject(SDL_Renderer*,SDL_Surface*,const char*,int,int);

	//GameObject Rendering function
	void objectRender(SDL_Renderer*,int[18][19]);

	//Generate random SDL_Rect
	SDL_Rect generateRandomRect(vector<SDL_Rect>,int,int);

	~GameObject();

private:
	SDL_Texture * objectTexture;
	SDL_Rect objectLocation;
};

