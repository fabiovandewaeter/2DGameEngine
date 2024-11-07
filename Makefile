CXX = g++
SRC_DIR = src
BIN_DIR = Windows_bin
OBJ_DIR = obj
TARGET = $(BIN_DIR)/main
rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d)) # recursive wildcare ; example : $(call rwildcard,src,*.cpp)

# get all .cpp files
ifeq ($(OS),Windows_NT) # windows
SRC_FILES := $(call rwildcard,src,*.cpp)
else # macos and linux
SRC_FILES := $(call rwildcard,src,*.cpp)
endif

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

# compilation
$(TARGET): $(OBJ_FILES)
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

run: $(TARGET)
	./$(TARGET) 60
