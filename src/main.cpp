#include "Engine.h"
int main(int argc, char* argv[]) 
{
    
    Engine engine;

    if (engine.init())
    {
        engine.run();
    }

    return 0;

}