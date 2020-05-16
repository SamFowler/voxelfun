#pragma once
#include <SDL2/SDL.h>
#include <map>
#include <iostream>

//TODO: Mouse input needs work - not collecting relative mouse motion and only taking one mouse position per update frame. 
//      Need to explore updating mouse position multiple times per update.


typedef Uint8 mbutton;

struct pos2d {
    int x = 0;
    int y = 0;
};

struct ButtonState {
    bool state;
    Uint8 clicks;
    bool pressed;
    bool released;
    bool held;
};

class Mouse {
public:
    inline void BeginNewFrame() {
        for (auto & x : buttonStates) {
            x.second.pressed = false;
            x.second.released = false;
        }
    }

    inline void PrintButtonState(mbutton button) {
        std::cout << "S:" << buttonStates[button].state << " C:" << unsigned(buttonStates[button].clicks) << " P:" << buttonStates[button].pressed
                << " R:" << buttonStates[button].released << " H:" << buttonStates[button].held << " x:" << pos.x << " y:" << pos.y << std::endl;
    }

    pos2d pos;
    std::map<mbutton, ButtonState> buttonStates;
};


class Input {

public:

    Input();
    ~Input();

    void Collect();

	bool WasKeyPressed(SDL_Keycode);
	bool WasKeyReleased(SDL_Keycode);
	bool IsKeyHeld(SDL_Keycode);

    bool IsQuit();

    bool WasButtonPressed(mbutton);
    bool WasButtonReleased(mbutton);
    bool IsButtonHeld(mbutton);
    Uint8 ButtonClicks(mbutton);
    pos2d GetMousePos();


private:
    SDL_Event m_event;

    void BeginNewFrame();
    void PollEvents();

    void QuitEvent();
    void KeyDownEvent();
	void KeyUpEvent();

    void MouseButtonUpEvent();
    void MouseButtonDownEvent();
    void MouseMotionEvent();

    bool m_isQuit;
    std::map<SDL_Keycode, bool> m_held_keys;
	std::map<SDL_Keycode, bool> m_pressed_keys;
	std::map<SDL_Keycode, bool> m_released_keys;

    Mouse m_mouse;
};