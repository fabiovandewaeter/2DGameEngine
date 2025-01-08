# 2D GameEngine SDL

## Description

A small 2D game engine written in c++ and using SDL

The basic functionalities of a game engine are recreated with SDL in order to obtain maximum performance on specific game functionalities that I want to create

## SDL libraries
- SDL2
- SDL_image
- SDL_ttf
- SDL_mixer

## Commands

### Windows

#### Repository for Windows SDL libraries files

- files : https://github.com/fabiovandewaeter/windows-sdl-libraries-files

#### Compile with make
`mingw32-make windows`

#### Compile without make

`g++ src/*.cpp src/entities/*.cpp src/entities/states/*.cpp src/entities/AI/*.cpp src/systems/*.cpp src/map/*.cpp src/structures/*.cpp src/structures/passiveStructures/*.cpp src/structures/activeStructures/*.cpp src/actions/patterns/*.cpp src/actions/effects/*.cpp src/actions/*.cpp -o bin/main.exe -I include -L Windows_lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer`

##### run

`./bin/main.exe`

### MacOs

#### Install SDL libraries files

- `brew install sdl2_image`
- `brew install sdl2_tt`
- `brew install sdl2_mixer`

#### Compile with make
`make` or `make SANITIZER=1`

#### Compile without make

`g++ src/*.cpp src/entities/*.cpp src/entities/states/*.cpp src/entities/AI/*.cpp src/systems/*.cpp src/map/*.cpp src/structures/*.cpp src/structures/passiveStructures/*.cpp src/structures/activeStructures/*.cpp src/actions/patterns/*.cpp src/actions/effects/*.cpp src/actions/*.cpp -I include -I/opt/homebrew/opt/sdl2/include/SDL2 -I/opt/homebrew/opt/sdl2_image/include/SDL2/ -I/opt/homebrew/opt/sdl2_ttf/include/SDL2 -I/opt/homebrew/opt/sdl2_mixer/include/SDL2 -L/opt/homebrew/opt/sdl2/lib -L/opt/homebrew/opt/sdl2_image/lib -L/opt/homebrew/opt/sdl2_ttf/lib -L/opt/homebrew/opt/sdl2_mixer/lib -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer`

##### run

`./a.out`

### Linux (no root)

#### Install SDL libraries files

* SDL2
```bash
git clone https://github.com/libsdl-org/SDL.git -b SDL2
./autogen.sh
./configure --prefix=$HOME/libs/SDL2
make
make install
export LD_LIBRARY_PATH=$HOME/libs/SDL2/lib:$LD_LIBRARY_PATH
```
* SDL_image:
```bash
wget https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.5.tar.gz
tar -xzf SDL2_image-2.0.5.tar.gz
./configure --prefix=$HOME/libs/SDL2
make
make install
```
* SDL_ttf:
```bash
wget https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.22.0.tar.gz
tar -xzf SDL2_ttf-2.22.0.tar.gz
./configure --prefix=$HOME/libs/SDL2
make
make install
```
* SDL_mixer:
```bash
wget https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-2.8.0.tar.gz
tar -xzf SDL2_mixer-2.8.0.tar.gz
./configure --prefix=$HOME/libs/SDL2
make
make install
```

#### Compile with make

`make macos`

#### Compile without make

`g++ src/*.cpp src/entities/*.cpp src/entities/states/*.cpp src/entities/AI/*.cpp src/systems/*.cpp src/map/*.cpp src/structures/*.cpp src/structures/passiveStructures/*.cpp src/structures/activeStructures/*.cpp src/actions/patterns/*.cpp src/actions/effects/*.cpp src/actions/*.cpp -I include -I$HOME/libs/SDL2/include -L$HOME/libs/SDL2/lib -lSDL2 -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer`

##### run

`./a.out`

##### Tracy profiler

https://github.com/wolfpld/tracy

`cmake -B profiler/build -S profiler -DCMAKE_BUILD_TYPE=Release -DTRACY_USE_LEGACY=ON -DLEGACY=ON`

`export SDKROOT=$(xcrun --sdk macosx --show-sdk-path)`

`cmake -B profiler/build -S profiler -DCMAKE_BUILD_TYPE=Release -DLEGACY=ON -DCMAKE_CXX_FLAGS="-Wno-deprecated-declarations" -DCMAKE_C_COMPILER=/usr/bin/clang -DCMAKE_CXX_COMPILER=/usr/bin/clang++ -DCMAKE_CXX_COMPILER=gcc-14 -DCMAKE_OSX_SYSROOT=/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -DCMAKE_ASM_COMPILER=/opt/homebrew/bin/as -DCMAKE_GIT_EXECUTABLE=/opt/homebrew/bin/git`

`cmake --build profiler/build --config Release --parallel`

`cd profiler/build`

`./tracy-profiler`

## How to add things

### images

add 1 px of padding to iamges
