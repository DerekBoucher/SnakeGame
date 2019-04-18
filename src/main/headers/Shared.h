//
//  Shared.h
//  snakeGame
//
//  Created by Derek Boucher on 20ARENA_SIZE_ROW-03-07.
//  Copyright © 20ARENA_SIZE_ROW Derek Boucher. All rights reserved.
//

#ifndef Shared_h
#define Shared_h
#include "SDL.h"

#define MOVE_UP 1
#define MOVE_DOWN 3
#define MOVE_LEFT 2
#define MOVE_RIGHT 4
#define ARENA_SIZE_ROW 16
#define ARENA_SIZE_COL 19
#define SCORE_BUFFER_SIZE 320
#define TILE_SIZE 40

struct shared
{
public:
    static SDL_Event event;
};

#endif /* Shared_h */
