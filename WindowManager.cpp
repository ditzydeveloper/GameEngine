#include "WindowManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>;

using namespace std;


WindowManager::WindowManager() {


	mWindow = SDL_CreateWindow("GAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (mWindow == NULL) {
		SDL_Quit();
	}
	else {
		m_renderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (m_renderer == NULL) {
			printf("Renderer could not be created . SDL Error: %s\n", SDL_GetError());
		}
		else {

			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags)) {
				printf("SDL_image could not initalize!  SDL_image Error: %s\n", IMG_GetError());
			}
		}
	};

};

WindowManager::~WindowManager() {

}

void  WindowManager::init() {
	SDL_Start();
	m_screenSurface = SDL_GetWindowSurface(mWindow);
}

void WindowManager::SDL_Start() {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
		cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return; // Exit or handle the error appropriately
	}
	else {
		return;
	}

}

void WindowManager::SDL_cleanUp() {
	SDL_FreeSurface(m_image);
	m_image = NULL;
	SDL_DestroyTexture(m_texture);
	m_texture = nullptr;
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(mWindow);
	mWindow = nullptr;
	m_renderer = nullptr;
	IMG_Quit();
	SDL_Quit();

}




SDL_Renderer* WindowManager::getRenderer() {
	return m_renderer;
}