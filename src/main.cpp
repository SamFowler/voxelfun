#include "Engine.hpp"
int main(int argc, char* argv[]) {
    
    Engine engine;



    if (engine.Init()) {
        engine.Run();
    }

    return 0;

}