#pragma once
#include <SDL.h>
#include <iostream>

class LTexture
{
public:
	LTexture();

	~LTexture();

	bool loadFromFile(std::string path, SDL_Renderer* renderer);

	//deallocatres texture
	void free();

	// render texture at given point
	// clip defines which portion of the texture we wish to render in case there is something like a sprite sheet. 
	void render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip = nullptr);

	//get dimensions of image
	int getWidth();
	int getHeight();
	SDL_Texture* getTexture();


private:
	SDL_Texture* mTexture;
	//Image dimensions
	int mWidth;
	int mHeight;
};

