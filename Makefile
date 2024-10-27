# Variables communes
CXX = g++
SRC_DIR = src
BIN_DIR = Windows_bin
OBJ_DIR = obj
TARGET = $(BIN_DIR)/main


# Récupère automatiquement tous les fichiers .cpp et génère les fichiers objets correspondants
ifeq ($(OS),Windows_NT)
    # Windows
    SRC_FILES := $(shell powershell -Command "Get-ChildItem -Recurse -Path '$(SRC_DIR)' -Filter '*.cpp' | Select-Object -ExpandProperty FullName")
else
    # macOS ou autres Unix
    SRC_FILES := $(shell find $(SRC_DIR) -name "*.cpp")
endif

OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Flags de compilation
CXXFLAGS = -I include
SDL_LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

# Cibles spécifiques à Windows
windows: CXXFLAGS += -L Windows_lib
windows: SDL_LIBS += -lmingw32 -lSDL2main
windows: $(TARGET)

# Cibles spécifiques à macOS
macos: CXXFLAGS += -I$(HOME)/libs/SDL2/include -L$(HOME)/libs/SDL2/lib \
                   -I/opt/homebrew/opt/sdl2/include/SDL2 -I/opt/homebrew/opt/sdl2_image/include/SDL2/
macos: SDL_LIBS += -L/opt/homebrew/opt/sdl2/lib -L/opt/homebrew/opt/sdl2_image/lib
macos: $(TARGET)


SRC = src
OBJ = obj

SOURCES = $(wildcard $(SRC)/*.cpp)
OBJECTS = $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SOURCES))

all: $(OBJECTS)
	echo "test1"
	g++ $^ -o $@

IL PASSE PAS PAR CELUI DU BAS
$(OBJ)/%.o: $(SRC)/%.cpp
	echo "test2"
	@if not exist $(OBJ) mkdir $(OBJ)
	g++ -I$(SRC) -c $< -o $@

# Compilation finale (linking)
$(TARGET): $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) -o $(TARGET) $(CXXFLAGS) $(SDL_LIBS)

# Compilation des fichiers objets
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	echo "test"
	@if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
	echo $(CXXFLAGS)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# Règle pour nettoyer les fichiers objets et l'exécutable
clean:
ifeq ($(OS),Windows_NT)
	del /Q $(OBJ_FILES) $(TARGET)  # Pour Windows
else
	rm -f $(OBJ_FILES) $(TARGET)  # Pour Unix
endif

# Exécuter le programme
run: $(TARGET)
	./$(TARGET) 60
