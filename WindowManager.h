#pragma once

#include <SDL.h>
#include <iostream>



class WindowManager
{
public:

	const static int SCREEN_WIDTH = 800;
	const static int SCREEN_HEIGHT = 600;

	// lazy foo's variables
// tthe surface contained by tghe window
	SDL_Surface* m_screenSurface = nullptr;
	// the image we will load and show on the screen
	SDL_Surface* m_image = nullptr;
	SDL_Window* mWindow = nullptr;

private:
	SDL_Renderer* m_renderer = nullptr;
	SDL_Texture* m_texture = nullptr;
	Uint32* m_buffer = nullptr;
	void SDL_Start();

public:
	WindowManager();
	~WindowManager();
	void init();
	void SDL_cleanUp();
	//void update();
	//void clear();
	SDL_Renderer* getRenderer();
};


