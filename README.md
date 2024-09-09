# 2D GameEngine SDL

## Description

A small 2D game engine written in c++ and using SDL

The basic functionalities of a game engine are recreated from scratch in order to obtain maximum performance on specific game functionalities that I want to create

## Commands

Windows :

```g++ src/*.cpp src/entities/*.cpp src/systems/*.cpp src/map/*.cpp src/objects/staticObjects/*.cpp -o Windows_bin/main -I include -L Windows_lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image ; .\Windows_bin\main.exe```

MacOs:

```g++ src/*.cpp src/entities/*.cpp src/systems/*.cpp -I/opt/homebrew/opt/sdl2/include/SDL2 -I/opt/homebrew/opt/sdl2_image/include/SDL2/ -L/opt/homebrew/opt/sdl2/lib -L/opt/homebrew/opt/sdl2_image/lib -lSDL2 -lSDL2_image ; ./a.out```

## SDL libraries
- SDL2
- SDL_image
