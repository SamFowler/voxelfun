#pragma once
#include "Input.hpp"

class Game 
{
public:
    bool init();
    bool update(Input& input);

private:
    bool m_is_running;
};