#include "Input.hpp"
#include <iostream>

Input::Input( ) {
}

Input::~Input( ) {
    
}

void Input::Collect() {
    BeginNewFrame();
    PollEvents();
}

void Input::BeginNewFrame() {
    m_isQuit = false;
    m_pressed_keys.clear();
	m_released_keys.clear();

    m_mouse.BeginNewFrame();
}

void Input::PollEvents() {
    while (SDL_PollEvent( &m_event ) != 0) {
        switch (m_event.type) {
            case SDL_QUIT:
                QuitEvent();
                break;
            case SDL_KEYDOWN:
                KeyDownEvent();
                break;
            case SDL_KEYUP:
                KeyUpEvent();
                break;
            case SDL_MOUSEMOTION:
                MouseMotionEvent();
                break;
            case SDL_MOUSEBUTTONDOWN:
                MouseButtonDownEvent();
                break;
            case SDL_MOUSEBUTTONUP:
                MouseButtonUpEvent();
                break;
        }
    }
}

bool Input::WasKeyPressed(SDL_Keycode key) {
	return m_pressed_keys[key];
}

bool Input::WasKeyReleased(SDL_Keycode key) {
	return m_released_keys[key];
}

bool Input::IsKeyHeld(SDL_Keycode key) {
	return m_held_keys[key];
}

bool Input::IsQuit() {
    return m_isQuit;
}

void Input::QuitEvent() {
    m_isQuit = true;
}

bool Input::WasButtonPressed(mbutton buttonEnum) {
    return m_mouse.buttonStates[buttonEnum].pressed;
}
bool Input::WasButtonReleased(mbutton buttonEnum) {
    return m_mouse.buttonStates[buttonEnum].released;
}
bool Input::IsButtonHeld(mbutton buttonEnum) {
    return m_mouse.buttonStates[buttonEnum].held;
}

Uint8 Input::ButtonClicks(mbutton buttonEnum) {
    return m_mouse.buttonStates[buttonEnum].clicks;
}

pos2d Input::GetMousePos() {
    return m_mouse.pos;
}


void Input::KeyDownEvent() {
	m_pressed_keys[m_event.key.keysym.sym] = true;
	m_held_keys[m_event.key.keysym.sym] = true;
}

void Input::KeyUpEvent() {
	m_released_keys[m_event.key.keysym.sym] = true;
	m_held_keys[m_event.key.keysym.sym] = false;
}

void Input::MouseButtonDownEvent() {
    m_mouse.buttonStates[m_event.button.button].pressed = true;
    m_mouse.buttonStates[m_event.button.button].clicks = m_event.button.clicks;
    m_mouse.buttonStates[m_event.button.button].held = true;
    m_mouse.buttonStates[m_event.button.button].state = true;
}

void Input::MouseButtonUpEvent() {
    m_mouse.buttonStates[m_event.button.button].released = true;
    m_mouse.buttonStates[m_event.button.button].clicks = m_event.button.clicks;
    m_mouse.buttonStates[m_event.button.button].held = false;
    m_mouse.buttonStates[m_event.button.button].state = false;
}

void Input::MouseMotionEvent() {
    SDL_GetMouseState(&m_mouse.pos.x, &m_mouse.pos.y);
}



