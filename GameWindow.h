#pragma once

#ifndef SCREEN_H_
#define SCREEN_H_
#include <SDL.h>
#include <iostream>

class GameWindow
{

public:
	const static int SCREEN_WIDTH = 800;
	const static int SCREEN_HEIGHT = 600;

	// lazy foo's variables
	// tthe surface contained by tghe window
	SDL_Surface* m_screenSurface = NULL;
	// the image we will load and show on the screen
	SDL_Surface* m_image = NULL;
	SDL_Window* m_window = NULL;

	enum KeyPressSurfaces {
		KEY_PRESS_SURFACE_DEFAULT,
		KEY_PRESS_SURFACE_UP,
		KEY_PRESS_SURFACE_DOWN, 
		KEY_PRESS_SURFACE_LEFT,
		KEY_PRESS_SURFACE_RIGHT,
		KEY_PRESS_SURFACE_TOTAL
	};

	SDL_Surface* m_KeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

	//Current displayed image
	SDL_Surface* m_currentSurface = nullptr;

private:
	
	SDL_Renderer* m_renderer = nullptr;
	SDL_Texture* m_texture;
	Uint32* m_buffer;
	void SDL_Start();




public:
	GameWindow();
	~GameWindow();
	bool init();
	bool processEvents();
	bool processEvents_shapes();
	bool loadMedia();
	bool loadMedia_texture();
	void SDL_cleanUp();
	void update();
	void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
	void clear();
	SDL_Surface* loadSurface(std::string path);
	SDL_Texture* loadTexture(std::string path);



};




#endif /* SCREEN_H_ */