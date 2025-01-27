#include "TextureManager.h"
#include <SDL.h>
#include "LTexture.h"
#include <map>



TextureManager::TextureManager() {

}


TextureManager::~TextureManager() {
	// free the renderer here ??

}

void TextureManager::setRenderer(SDL_Renderer* renderer) {
	gRenderer = renderer;
	if (gRenderer == nullptr) {
		printf("renderer not init");
	}
}


bool TextureManager::load(std::string filePath, std::string id) {
	bool success = true;
	LTexture* newTexture = new LTexture();

	if (!newTexture->loadFromFile(filePath, gRenderer)) {
		printf("Unable to load texture");
		delete newTexture;
		success = false;
	}

	textureMap[id] = *newTexture;
	return success;
}


void TextureManager::draw(std::string id, int x, int y, int w, int h, double scale, double theta, SDL_RendererFlip flip) {

	SDL_Rect sourceRect, destinationRect;

	sourceRect.x = 0;
	sourceRect.y = 0;
	sourceRect.w = destinationRect.w = textureMap[id].getWidth();
	sourceRect.h = destinationRect.h = textureMap[id].getHeight();
	destinationRect.x = x;
	destinationRect.y = y;
	destinationRect.w *= scale;
	destinationRect.h *= scale;

	std::cout << "Renderer pointer: " << gRenderer << std::endl;
	if (gRenderer == nullptr) {
		std::cerr << "Renderer is not initialized!" << std::endl;
	}
	if (textureMap.find(id) == textureMap.end()) {
		std::cerr << "Error: Texture ID not found in textureMap: " << id << std::endl;
		return;
	}
	if (textureMap[id].getTexture() == nullptr) {
		printf("texture goes null in textureManager.draw()");
	}


	if (SDL_RenderCopy(gRenderer, textureMap[id].getTexture(), NULL, &destinationRect)) {
		std::cerr << "SDL_RenderCopyEx Error: " << SDL_GetError() << std::endl;
	}

	//SDL_RenderCopyEx(gRenderer, textureMap[id].getTexture(), &sourceRect, &destinationRect, theta, NULL, flip);
}


void TextureManager::drawFrame(std::string id, int x, int y, int w, int h, int currentRow, int currentFrame, double scale, double theta, SDL_Point* center, SDL_RendererFlip flip) {

	SDL_Rect sourceRect, destinationRect;

	sourceRect.x = w * currentFrame;
	sourceRect.y = h * currentRow;
	sourceRect.w = destinationRect.w = w;
	sourceRect.h = destinationRect.h = h;
	destinationRect.x = x;
	destinationRect.y = y;
	destinationRect.w *= scale;
	destinationRect.h *= scale;

	SDL_RenderCopyEx(gRenderer, textureMap[id].getTexture(), &sourceRect, &destinationRect, theta, NULL, flip);
}

void TextureManager::render(std::string id, int x, int y, SDL_Rect* clip) {
	// Set Rendering space and render to screen
	SDL_Rect renderQuad = { x, y, textureMap[id].getWidth(), textureMap[id].getHeight()};


	if (clip != nullptr) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	if (SDL_RenderCopy(gRenderer, textureMap[id].getTexture(), clip, &renderQuad)) {
		std::cerr << "SDL_RenderCopy Error: " << SDL_GetError() << std::endl;
	}

	// Here you see why we needed a wrapper class.Up until now, we have been pretty much been rendering full screen images so we didn't need to specify position.
	// Because we didn't need to specify position, we just called SDL_RenderCopy with the last two arguments as NULL.
	// When rendering a texture in a certain place, you need to specify a destination rectangle that sets the x / y position and width / height.
	// We can't specify the width/height without knowing the original image's dimensions.So here when we render our texture we create a rectangle with the position arguments and the member width / height, 
	// and pass in this rectangle to SDL_RenderCopy.
}


void TextureManager::setColor(std::string id, Uint8 red, Uint8 green, Uint8 blue) {
	SDL_SetTextureColorMod(textureMap[id].getTexture(), red, green, blue);
}

void TextureManager::setBlendMode(std::string id, SDL_BlendMode blending) {
	SDL_SetTextureBlendMode(textureMap[id].getTexture(), blending);
}

void TextureManager::setAlpha(std::string id, Uint8 alpha) {
	SDL_SetTextureAlphaMod(textureMap[id].getTexture(), alpha);
}

void TextureManager::deleteTexture(std::string id) {
	textureMap.erase(id);
}
