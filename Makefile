# Variables communes
CXX = g++
SRC_DIR = src
BIN_DIR = Windows_bin
OBJ_DIR = obj
TARGET = $(BIN_DIR)/main
rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

# Récupère automatiquement tous les fichiers .cpp et génère les fichiers objets correspondants
ifeq ($(OS),Windows_NT)
#SRC_FILES := $(shell powershell -Command "Get-ChildItem -Recurse -Path '$(SRC_DIR)' -Filter '*.cpp' | Select-Object -ExpandProperty FullName")
#SRC_FILES := $(shell powershell -Command "Get-ChildItem -Path src -File -Recurse | ForEach-Object { $_.FullName.Replace((Get-Location).Path + \"\\\", '').Replace(\"\\\", '/') }")
#SRC_FILES := $(shell powershell -Command "Get-ChildItem -Path '$(SRC_DIR)' -File -Recurse | Select-Object -ExpandProperty FullName | ForEach-Object { $_.FullName.Replace((Get-Location).Path + '\', '').Replace('\', '/') }")
#SRC_FILES := $(shell powershell -Command "Get-ChildItem -Path '$(SRC_DIR)' -File -Recurse | Select-Object -ExpandProperty FullName | ForEach-Object { $_.FullName.Replace((Get-Location).Path + '\', '').Replace('\', '/') }")
#SRC_FILES := $(shell find . -name '*.cpp')
SRC_FILES := $(call rwildcard,src,*.cpp)
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
windows: SDL_LIBS := -lmingw32 -lSDL2main $(SDL_LIBS)
windows: $(TARGET)

# Cibles spécifiques à macOS
macos: CXXFLAGS += -I$(HOME)/libs/SDL2/include -L$(HOME)/libs/SDL2/lib \
                   -I/opt/homebrew/opt/sdl2/include/SDL2 -I/opt/homebrew/opt/sdl2_image/include/SDL2/
macos: SDL_LIBS += -L/opt/homebrew/opt/sdl2/lib -L/opt/homebrew/opt/sdl2_image/lib
macos: $(TARGET)
#${info Files $(SRC_FILES)}
#$(call rwildcard,src,*.cpp)
# Compilation finale (linking)
$(TARGET): $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) -o $(TARGET) $(CXXFLAGS) $(SDL_LIBS)

# Compilation des fichiers objets
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
ifeq ($(OS),Windows_NT)
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
else
	@mkdir -p $(dir $@)
endif
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
