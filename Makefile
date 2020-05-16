CXX       := g++
CXX_FLAGS := -std=c++17 -ggdb -Wall -g -Wno-unused-function
C_FLAGS   := `sdl2-config --cflags --libs`
LINKER_FLAGS := -lSDL2 -lSDL2main -lGL -lGLEW

BIN     := bin
SRC     := src
INCLUDE := include

LIBRARIES   := 
EXECUTABLE  := mygame



all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $^ $(LINKER_FLAGS) -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*