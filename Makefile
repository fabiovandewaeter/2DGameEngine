CXX = g++
SRC_DIR = src
BIN_DIR = bin
OBJ_DIR = obj
TARGET = $(BIN_DIR)/main
WINDOWS_TARGET = $(BIN_DIR)\main.exe
rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d)) # recursive wildcard

# Detect OS
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    PLATFORM = linux
else ifeq ($(UNAME_S),Darwin)
    PLATFORM = macos
else
    PLATFORM = windows
endif

# get all .cpp files
SRC_FILES := $(call rwildcard,src,*.cpp)
HEADER_FILES := $(call rwildcard,include,*.hpp)

# get the path of all .o to generate
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Base flags for compilation
CXXFLAGS = -I include -O2 -Wall -Wextra -Wpedantic -std=c++11 -DTRACY_ENABLE
SDL_LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
SANITIZE_FLAGS = -fsanitize=address -fsanitize=undefined

# Platform-specific flags
ifeq ($(PLATFORM),windows)
    CXXFLAGS += -L Windows_lib
    SDL_LIBS := -lmingw32 -lSDL2main $(SDL_LIBS)
else ifeq ($(PLATFORM),macos)
    CXXFLAGS += -I/opt/homebrew/opt/sdl2/include/SDL2 -I/opt/homebrew/opt/sdl2_image/include/SDL2/
    SDL_LIBS += -L/opt/homebrew/opt/sdl2/lib -L/opt/homebrew/opt/sdl2_image/lib -L/opt/homebrew/opt/sdl2_ttf/lib -L/opt/homebrew/opt/sdl2_mixer/lib
else ifeq ($(PLATFORM),linux)
    CXXFLAGS += -I$(HOME)/libs/SDL2/include -L$(HOME)/libs/SDL2/lib
endif

# Optional sanitizer flag (default is empty)
SANITIZER ?= 0

ifeq ($(SANITIZER),1)
    CXXFLAGS += $(SANITIZE_FLAGS) -DPROFILER
endif

# Main target
all: $(TARGET)
	make run

# Compilation
$(TARGET): $(OBJ_FILES) obj/microui.o $(HEADER_FILES)
ifeq ($(PLATFORM),windows)
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
else
	@mkdir -p $(dir $@)
endif
	$(CXX) $(OBJ_FILES) obj/microui.o -o  $(TARGET) $(CXXFLAGS) $(SDL_LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
ifeq ($(PLATFORM),windows)
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
else
	@mkdir -p $(dir $@)
endif
	$(CXX) -c $< -o $@ $(CXXFLAGS)

obj/microui.o: $(SRC_DIR)/microui.c
	gcc -c src/microui.c -o obj/microui.o -I include

# Cleaning
clean:
ifeq ($(PLATFORM),windows)
	del /Q $(OBJ_FILES) $(TARGET)
else
	rm -f $(OBJ_FILES) $(TARGET)
endif

# Run the program
run:
ifeq ($(PLATFORM),windows)
	.\$(WINDOWS_TARGET) 60
else
	./$(TARGET) 60
endif
