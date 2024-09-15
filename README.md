# 2D GameEngine SDL

## Description

A small 2D game engine written in c++ and using SDL

The basic functionalities of a game engine are recreated from scratch in order to obtain maximum performance on specific game functionalities that I want to create

## Commands

Windows :

`g++ src/*.cpp src/entities/*.cpp src/systems/*.cpp src/map/*.cpp src/staticObjects/*.cpp -o Windows_bin/main -I include -L Windows_lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf ; .\Windows_bin\main.exe`

MacOs:

`g++ src/*.cpp src/entities/*.cpp src/systems/*.cpp src/staticObjects/*.cpp -I/opt/homebrew/opt/sdl2/include/SDL2 -I/opt/homebrew/opt/sdl2_image/include/SDL2/ -L/opt/homebrew/opt/sdl2/lib -L/opt/homebrew/opt/sdl2_image/lib -lSDL2 -lSDL2_image -lSDL2_ttf ; ./a.out`

Linux (no root):

* SDL2
```
git clone https://github.com/libsdl-org/SDL.git -b SDL2
./autogen.sh
./configure --prefix=$HOME/libs/SDL2
make
make install
export LD_LIBRARY_PATH=$HOME/libs/SDL2/lib:$LD_LIBRARY_PATH
```
* SDL_image:
```
wget https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.5.tar.gz
./configure --prefix=$HOME/libs/SDL2
```

`g++ src/*.cpp src/entities/*.cpp src/systems/*.cpp src/map/*.cpp src/staticObjects/*.cpp -I include -I$HOME/libs/SDL2/include -L$HOME/libs/SDL2/lib -lSDL2 -I/opt/homebrew/opt/sdl2/include/SDL2 -I/opt/homebrew/opt/sdl2_image/include/SDL2/ -L/opt/homebrew/opt/sdl2/lib -L/opt/homebrew/opt/sdl2_image/lib -lSDL2 -lSDL2_image -lSDL2_ttf`

## SDL libraries
- SDL2
- SDL_image
- SDL_ttf