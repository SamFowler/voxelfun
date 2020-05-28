#include "Input.hpp"
#include <iostream>

Input::Input( )
{
}

Input::~Input( )
{
    
}

bool Input::init()
{
    SDL_SetRelativeMouseMode(SDL_TRUE);
    if (SDL_SetRelativeMouseMode(SDL_TRUE) < 0)
    {
        std::cout << "Could not set SDL relative mouse mode" << std::endl;
       return false;
    }

    return true;
}

void Input::collect()
{
    beginNewFrame();
    pollEvents();
}

void Input::beginNewFrame()
{
    m_is_quit = false;
    m_pressed_keys.clear();
	m_released_keys.clear();

    m_mouse.beginNewFrame();
}

void Input::pollEvents()
{
    while (SDL_PollEvent( &m_event ) != 0) 
    {
        switch (m_event.type) 
        {
            case SDL_QUIT:
                quitEvent();
                break;
            case SDL_KEYDOWN:
                keyDownEvent();
                break;
            case SDL_KEYUP:
                keyUpEvent();
                break;
            case SDL_MOUSEMOTION:
                mouseMotionEvent();
                break;
            case SDL_MOUSEBUTTONDOWN:
                mouseButtonDownEvent();
                break;
            case SDL_MOUSEBUTTONUP:
                mouseButtonUpEvent();
                break;
        }
    }
}

bool Input::wasKeyPressed(const SDL_Keycode key)
{
	return m_pressed_keys[key];
}

bool Input::wasKeyReleased(const SDL_Keycode key)
{
	return m_released_keys[key];
}

bool Input::isKeyHeld(const SDL_Keycode key)
{
	return m_held_keys[key];
}

bool Input::isQuit() const
{
    return m_is_quit;
}

void Input::quitEvent()
{
    m_is_quit = true;
}

bool Input::wasButtonPressed(const mbutton buttonEnum)
{
    return m_mouse.button_states[buttonEnum].pressed;
}
bool Input::wasButtonReleased(const mbutton buttonEnum)
{
    return m_mouse.button_states[buttonEnum].released;
}
bool Input::isButtonHeld(const mbutton buttonEnum)
{
    return m_mouse.button_states[buttonEnum].held;
}

Uint8 Input::buttonClicks(const mbutton buttonEnum)
{
    return m_mouse.button_states[buttonEnum].clicks;
}

glm::ivec2 Input::getMousePos() const
{
    return m_mouse.pos;
}

glm::ivec2 Input::getRelMousePos() const
{
    return m_mouse.rel_pos;
}


void Input::keyDownEvent()
{
	m_pressed_keys[m_event.key.keysym.sym] = true;
	m_held_keys[m_event.key.keysym.sym] = true;
}

void Input::keyUpEvent()
{
	m_released_keys[m_event.key.keysym.sym] = true;
	m_held_keys[m_event.key.keysym.sym] = false;
}

void Input::mouseButtonDownEvent()
{
    m_mouse.button_states[m_event.button.button].pressed = true;
    m_mouse.button_states[m_event.button.button].clicks = m_event.button.clicks;
    m_mouse.button_states[m_event.button.button].held = true;
    m_mouse.button_states[m_event.button.button].state = true;
}

void Input::mouseButtonUpEvent()
{
    m_mouse.button_states[m_event.button.button].released = true;
    m_mouse.button_states[m_event.button.button].clicks = m_event.button.clicks;
    m_mouse.button_states[m_event.button.button].held = false;
    m_mouse.button_states[m_event.button.button].state = false;
}

void Input::mouseMotionEvent()
{
    m_mouse.rel_pos.x += m_event.motion.xrel;
    m_mouse.rel_pos.y += m_event.motion.yrel;
    SDL_GetMouseState(&m_mouse.pos.x, &m_mouse.pos.y);
}



