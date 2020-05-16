#pragma once
#include <SDL2/SDL.h>
#include <map>

class Input {

public:

    Input();
    ~Input();

    void StartNewFrame();
    void PollEvents();
    void Collect();



	bool wasKeyPressed(SDL_Keycode);
	bool wasKeyReleased(SDL_Keycode);
	bool isKeyHeld(SDL_Keycode);
    bool isQuit();

private:
    SDL_Event m_event;

    void beginNewFrame();
    void quitEvent();
    void keyDownEvent();
	void keyUpEvent();

    bool m_isQuit;
    std::map<SDL_Keycode, bool> m_held_keys;
	std::map<SDL_Keycode, bool> m_pressed_keys;
	std::map<SDL_Keycode, bool> m_released_keys;

};