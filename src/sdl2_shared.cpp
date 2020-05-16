#ifndef SDL2SHARED
#define SDL2SHARED

#include <memory>
#include <SDL2/SDL.h>

static void SDL_DelRes(SDL_Window* r) { SDL_DestroyWindow(r); }
//static void SDL_DelRes(SDL_Renderer* r) { SDL_DestroyRenderer(r); }
//static void SDL_DelRes(SDL_Texture* r) { SDL_DestroyTexture(r); }

template <typename T> std::shared_ptr<T> sdl_shared(T* t) {
	return std::shared_ptr<T>(t, [](T* t) {SDL_DelRes(t); });
}

#endif