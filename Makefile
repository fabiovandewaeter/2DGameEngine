CXX = g++
CXXVERSION = -std=c++14
SRC_DIR = src
BIN_DIR = bin
OBJ_DIR = obj
rwildcard=$(foreach d,$(wildcard $(1)/*),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
SRC_FILES := $(call rwildcard,src,*.cpp)
HEADER_FILES := $(call rwildcard,include,*.hpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))
DEP_FILES = $(OBJ_FILES:.o=.d) # Dependency files
TARGET = $(BIN_DIR)/main
WINDOWS_TARGET = $(BIN_DIR)\main.exe

# Detect OS
ifeq ($(OS),Windows_NT)
    PLATFORM = windows
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        PLATFORM = linux
    else ifeq ($(UNAME_S),Darwin)
        PLATFORM = macos
    endif
endif

# Base flags for compilation
CXXFLAGS = -I include -O2 -Wall -Wextra -Wpedantic $(CXXVERSION) -MMD -MP
SDL_LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
SANITIZE_FLAGS = 
ifneq ($(PLATFORM),windows)
SANITIZE_FLAGS = -fsanitize=address -fsanitize=undefined
endif

# Platform-specific flags
ifeq ($(PLATFORM),windows)
    CXXFLAGS += -L Windows_lib
    SDL_LIBS := -lmingw32 -lSDL2main -lws2_32 -ldbghelp $(SDL_LIBS)
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
else ifeq ($(SANITIZER), 2)
    CXXFLAGS += $(SANITIZE_FLAGS) -fsanitize=thread -DPROFILER
endif

TRACY?= 0

ifeq ($(TRACY),1)
    CXXFLAGS += $(SANITIZE_FLAGS) -DTRACY_ENABLE
endif

# Main target
all: $(TARGET)
ifeq ($(OS),Windows_NT)
	mingw32-make run
else
	make run
endif

ifeq ($(PLATFORM),windows)
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
else
	@mkdir -p $(dir $@)
endif
-include $(DEP_FILES) # Include dependency files

# Compilation
$(TARGET): $(OBJ_FILES) obj/microui/microui.o
ifeq ($(PLATFORM),windows)
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
else
	@mkdir -p $(dir $@)
endif
	$(CXX) $(OBJ_FILES) obj/microui/microui.o -o  $(TARGET) $(CXXFLAGS) $(SDL_LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
ifeq ($(PLATFORM),windows)
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
else
	@mkdir -p $(dir $@)
endif
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(OBJ_DIR)/microui/microui.o: $(SRC_DIR)/microui/microui.c
ifeq ($(PLATFORM),windows)
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
else
	@mkdir -p $(dir $@)
endif
	gcc -c $< -o $@ -I include

clean:
ifeq ($(PLATFORM),windows)
	rmdir /s /q $(OBJ_DIR)
else
	rm -rf $(OBJ_DIR)
endif

run:
	./$(TARGET) 60

# ================ TESTS ================

TEST_FILES := $(call rwildcard,tests,*.cpp)
TEST_TARGET = $(BIN_DIR)/tests
TEST_OBJ_DIR = $(OBJ_DIR)/tests
TEST_OBJ_FILES = $(patsubst tests/%.cpp, $(TEST_OBJ_DIR)/%.o, $(TEST_FILES))
TEST_CXXVERSION = -std=c++20
TEST_CXXFLAGS = -I include -O2 $(TEST_CXXVERSION)

ifeq ($(PLATFORM),windows)
    TEST_CXXFLAGS += -L Windows_lib
    SDL_LIBS := -lmingw32 -lSDL2main -lws2_32 -ldbghelp $(SDL_LIBS)
else ifeq ($(PLATFORM),macos)
    TEST_CXXFLAGS += -I/opt/homebrew/opt/sdl2/include/SDL2 -I/opt/homebrew/opt/sdl2_image/include/SDL2/
    SDL_LIBS += -L/opt/homebrew/opt/sdl2/lib -L/opt/homebrew/opt/sdl2_image/lib -L/opt/homebrew/opt/sdl2_ttf/lib -L/opt/homebrew/opt/sdl2_mixer/lib
else ifeq ($(PLATFORM),linux)
    TEST_CXXFLAGS += -I$(HOME)/libs/SDL2/include -L$(HOME)/libs/SDL2/lib
endif

$(TEST_TARGET): $(TEST_OBJ_FILES)
ifeq ($(PLATFORM),windows)
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
else
	@mkdir -p $(dir $@)
endif
	$(CXX) $(TEST_OBJ_FILES) -o $(TEST_TARGET) $(TEST_CXXFLAGS) $(SDL_LIBS)

$(TEST_OBJ_DIR)/%.o: tests/%.cpp
ifeq ($(PLATFORM),windows)
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
else
	@mkdir -p $(dir $@)
endif
	$(CXX) -c $< -o $@ $(TEST_CXXFLAGS)

test: $(TEST_TARGET)
ifeq ($(PLATFORM),windows)
	.\$(TEST_TARGET)
else
	./$(TEST_TARGET)
endif

.PHONY: all clean run test
