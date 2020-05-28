#pragma once
#include <SDL2/SDL.h>
#include <map>
#include <iostream>
#include <glm/glm.hpp>

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
        rel_pos.x = 0;
        rel_pos.y = 0;
    }

    inline void printButtonState(mbutton button)
    {
        std::cout << "S:" << button_states[button].state << " C:" << unsigned(button_states[button].clicks) << " P:" << button_states[button].pressed
                << " R:" << button_states[button].released << " H:" << button_states[button].held << " x:" << pos.x << " y:" << pos.y 
                << " xrel:" << rel_pos.x << " yrel:" << rel_pos.y << std::endl;
    }

    glm::ivec2 pos;
    std::map<mbutton, ButtonState> button_states;
    glm::ivec2 rel_pos;
};


/*
    --------- Input class --------------------------------------------------------
*/
class Input 
{

public:

    Input();
    ~Input();

    bool init();
    void collect();

	bool wasKeyPressed(const SDL_Keycode);
	bool wasKeyReleased(const SDL_Keycode);
	bool isKeyHeld(const SDL_Keycode);

    bool isQuit() const;

    bool wasButtonPressed(const mbutton); 
    bool wasButtonReleased(const mbutton);
    bool isButtonHeld(const mbutton);
    Uint8 buttonClicks(const mbutton);
    glm::ivec2 getMousePos() const;
    glm::ivec2 getRelMousePos() const;
    inline void printMouse(const mbutton button) {m_mouse.printButtonState(button);}


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