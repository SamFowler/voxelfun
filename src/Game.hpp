#pragma once
#include "Input.hpp"

class Game {

public:
    bool Init();
    bool Update(Input& input);

private:
    bool m_isRunning;
};