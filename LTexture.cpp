#include "LTexture.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>


using namespace std;

LTexture::LTexture() {
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	// Deallocate
	free();
}


bool LTexture::loadFromFile(std::string path, SDL_Renderer* renderer)
{
	// get rid of preexisting texture
	free();

	SDL_Texture* newTexture = nullptr;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == nullptr) {
		printf("Unable to load image % s!SDL_image Error : % s\n", path.c_str(), IMG_GetError());
	}
	else {
		// color key image - a color key specifies a color in a surface ot be treated as transparent when a surface is blitted (copied) to another surface. 
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xff, 0xff));
		printf("checking if we are in the method\n");


		// create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == nullptr)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else {
			printf("check if we have a texture\n");
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}
	}
		// get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	std::cout << "load texture location:: " <<newTexture<< std::endl;
	mTexture = newTexture;
	return mTexture != nullptr;
}


void LTexture::free() {
	if (mTexture != nullptr) {
		SDL_DestroyTexture(mTexture);
		mTexture = nullptr;
		mWidth = 0;
		mHeight = 0;
	}
}

// clip exists if we have a sprite sheet and need to specify which area of the sprite sheet texture we wish to render.
void LTexture::render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip) {
	// Set Rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };


	if (clip != nullptr) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	if (SDL_RenderCopy(renderer, mTexture, clip, &renderQuad)) {
		std::cerr << "SDL_RenderCopy Error: " << SDL_GetError() << std::endl;
	}

	// Here you see why we needed a wrapper class.Up until now, we have been pretty much been rendering full screen images so we didn't need to specify position.
	// Because we didn't need to specify position, we just called SDL_RenderCopy with the last two arguments as NULL.
	// When rendering a texture in a certain place, you need to specify a destination rectangle that sets the x / y position and width / height.
	// We can't specify the width/height without knowing the original image's dimensions.So here when we render our texture we create a rectangle with the position arguments and the member width / height, 
	// and pass in this rectangle to SDL_RenderCopy.
}


int LTexture::getWidth() {
	return mWidth;
}

int LTexture::getHeight() {
	return mHeight;
}

SDL_Texture* LTexture::getTexture() {
	return mTexture;
}