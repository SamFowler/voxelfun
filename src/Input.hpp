#pragma once
#include <SDL2/SDL.h>
#include <map>
#include <iostream>

//TODO: Mouse input needs work - not collecting relative mouse motion and only taking one mouse position per update frame. 
//      Need to explore updating mouse position multiple times per update.


typedef Uint8 mbutton;

struct pos2d 
{
    int x = 0;
    int y = 0;
};

/*
    --------- ButtonState struct --------------------------------------------------------
*/
struct ButtonState 
{
    bool state;
    Uint8 clicks;
    bool pressed;
    bool released;
    bool held;
};

/*
    --------- Mouse class --------------------------------------------------------
*/
class Mouse 
{
public:
    inline void beginNewFrame() 
    {
        for (auto & x : button_states) 
        {
            x.second.pressed = false;
            x.second.released = false;
        }
    }

    inline void printButtonState(mbutton button) 
    {
        std::cout << "S:" << button_states[button].state << " C:" << unsigned(button_states[button].clicks) << " P:" << button_states[button].pressed
                << " R:" << button_states[button].released << " H:" << button_states[button].held << " x:" << pos.x << " y:" << pos.y << std::endl;
    }

    pos2d pos;
    std::map<mbutton, ButtonState> button_states;
};


/*
    --------- Input class --------------------------------------------------------
*/
class Input 
{

public:

    Input();
    ~Input();

    void collect();

	bool wasKeyPressed(SDL_Keycode);
	bool wasKeyReleased(SDL_Keycode);
	bool isKeyHeld(SDL_Keycode);

    bool isQuit();

    bool wasButtonPressed(mbutton);
    bool wasButtonReleased(mbutton);
    bool isButtonHeld(mbutton);
    Uint8 buttonClicks(mbutton);
    pos2d getMousePos();


private:
    SDL_Event m_event;

    void beginNewFrame();
    void pollEvents();

    void quitEvent();
    void keyDownEvent();
	void keyUpEvent();

    void mouseButtonUpEvent();
    void mouseButtonDownEvent();
    void mouseMotionEvent();

    bool m_is_quit;
    std::map<SDL_Keycode, bool> m_held_keys;
	std::map<SDL_Keycode, bool> m_pressed_keys;
	std::map<SDL_Keycode, bool> m_released_keys;

    Mouse m_mouse;
};