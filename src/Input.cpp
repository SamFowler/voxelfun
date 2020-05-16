#include "Input.hpp"
#include <iostream>

Input::Input( ) {
}

Input::~Input( ) {
    
}

void Input::Collect() {
    StartNewFrame();
    PollEvents();
}

void Input::StartNewFrame() {
    m_isQuit = false;
    m_pressed_keys.clear();
	m_released_keys.clear();
}

void Input::PollEvents() {
    while (SDL_PollEvent( &m_event ) != 0) {
        switch (m_event.type) {
            case SDL_QUIT:
                quitEvent();
                break;
            case SDL_KEYDOWN:
                keyDownEvent();
                break;
            case SDL_KEYUP:
                keyUpEvent();
                break;
        }
    }
}

bool Input::wasKeyPressed(SDL_Keycode key) {
	return m_pressed_keys[key];
}

bool Input::wasKeyReleased(SDL_Keycode key) {
	return m_released_keys[key];
}

bool Input::isKeyHeld(SDL_Keycode key) {
	return m_held_keys[key];
}

bool Input::isQuit() {
    return m_isQuit;
}


void Input::quitEvent() {
    m_isQuit = true;
}

void Input::keyDownEvent() {
	m_pressed_keys[m_event.key.keysym.sym] = true;
	m_held_keys[m_event.key.keysym.sym] = true;
}

void Input::keyUpEvent() {
	m_released_keys[m_event.key.keysym.sym] = true;
	m_held_keys[m_event.key.keysym.sym] = false;
}


