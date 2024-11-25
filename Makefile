CXX = g++
SRC_DIR = src
BIN_DIR = bin
OBJ_DIR = obj
TARGET = $(BIN_DIR)/main
WINDOWS_TARGET = $(BIN_DIR)\main.exe
rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d)) # recursive wildcare ; example : $(call rwildcard,src,*.cpp)

# get all .cpp files
SRC_FILES := $(call rwildcard,src,*.cpp)
HEADER_FILES := $(call rwildcard,include,*.hpp)

# get the path of all .o to generate
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

# flags for compilation
CXXFLAGS = -I include
SDL_LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

# flags for compilation (only used by Windows)
windows: CXXFLAGS += -L Windows_lib
windows: SDL_LIBS := -lmingw32 -lSDL2main $(SDL_LIBS)
windows: $(TARGET)

# flags for compilation (only used by macOS)
macos: CXXFLAGS += -I/opt/homebrew/opt/sdl2/include/SDL2 -I/opt/homebrew/opt/sdl2_image/include/SDL2/
macos: SDL_LIBS += -L/opt/homebrew/opt/sdl2/lib -L/opt/homebrew/opt/sdl2_image/lib -L/opt/homebrew/opt/sdl2_ttf/lib -L/opt/homebrew/opt/sdl2_mixer/lib
macos: $(TARGET)

# Flags de compilation pour Linux
linux: CXXFLAGS += -I$(HOME)/libs/SDL2/include -L$(HOME)/libs/SDL2/lib
linux: SDL_LIBS += -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
linux: $(TARGET)

# compilation
$(TARGET): $(OBJ_FILES) $(HEADER_FILES)
ifeq ($(OS),Windows_NT)
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
else
	@mkdir -p $(dir $@)
endif
	$(CXX) $(OBJ_FILES) -o $(TARGET) $(CXXFLAGS) $(SDL_LIBS)

# compilation of all .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
ifeq ($(OS),Windows_NT)
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
else
	@mkdir -p $(dir $@)
endif
	$(CXX) -c $< -o $@ $(CXXFLAGS)

clean:
ifeq ($(OS),Windows_NT)
	del /Q $(OBJ_FILES) $(TARGET)  # Pour Windows
else
	rm -f $(OBJ_FILES) $(TARGET)  # Pour Unix
endif

run:
ifeq ($(OS),Windows_NT)
	.\$(WINDOWS_TARGET) 60
else
	./$(TARGET) 60
endif
