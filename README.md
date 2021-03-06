# SnakeGame
Personal Snake Game project written in C/C++ using the SDL 2.0 library.
This project makes use of Premake5 to support cross platform building

Premake5 Repository : https://github.com/premake/premake-core

![](images/gameplay.png)

## How to build:

    1.  Clone Repository into arbitrary directory.
    2.  Open the command line or Terminal from the directory of the cloned repository.
    
    MAC OS X:
    **Only supports building with Xcode.
        3_1. From the Terminal, enter "premake5 xcode4".
        3_2. Open the generated .xcodeproj file.
        3_3. Build the project in Xcode.
        
    WINDOWS:
    **Only supports building with VS 2013, 2015, 2017 and 2019.
        3_4. From the Command Line, enter "premake5 vs20xx". (where xx = 13, 15, 17 or 19)
        3_5. Open the generated .sln file.
        3_6. Build the project in Visual Studio.

## Game Rules:

    1.  The goal of the game is to collect as much fruits as possible
    2.  A fruit can be collected by passing over its tile.
    3.  Every time a fruit is collected, the length of the snake grows by 1.
    4.  The game is over if one of these events occurs:
        
        4_1.  The player collides with any border of the game area.
        4_2.  The player collides with one of his snake parts.

### Controls:

    A -> Move left
    S -> Move down
    D -> Move Right
    W -> Move up
        
