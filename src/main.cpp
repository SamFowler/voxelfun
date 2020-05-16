#include "Engine.hpp"
int main(int argc, char* argv[]) {
    
    Engine engine;

    if (engine.init(640, 480)) {
        
        engine.run();
    }

    return 0;

}