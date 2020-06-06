CXX       := g++
CXX_FLAGS := -std=c++17 -ggdb -Wall -g -Wno-unused -Winvalid-pch
C_FLAGS   := `sdl2-config --cflags --libs`
LINKER_FLAGS := -lSDL2 -lSDL2main -lGL -lGLEW

BIN     := bin
SRC     := src
INCLUDE := include

LIBRARIES   := 
EXECUTABLE  := mygame

#g++ -std=c++17 -ggdb -Wall -g -H -Wno-unused -Winvalid-pch -c src/pch/pch_std.h #compile pch

PCH_SRC = pch_std.h

all: $(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp $(SRC)/*/*.cpp
	$(CXX) $(CXX_FLAGS) -$(INCLUDE) $(SRC)/pch/$(PCH_SRC) src/*.cpp src/*/*.cpp $(LINKER_FLAGS) -o $@ $(LIBRARIES)
