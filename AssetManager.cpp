#include "AssetManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include "TextureManager.h"



AssetManager::AssetManager() {

}

AssetManager::~AssetManager() {

}


bool AssetManager::loadMedia() {

	bool success = true;


	if (!textureManager.load("C:\\Users\\McAll\\OneDrive\\Pictures\\New folder\\14_animated_sprites_and_vsync\\foo.png", "test")) {
		printf("failed to load second texture image");
		success = false;
	}

	return success;
}



void AssetManager::setRenderer(SDL_Renderer* renderer) {
	textureManager.setRenderer(renderer);

}


/// init funcs:

void AssetManager::initManagmentSystems(TextureManager textureM, SDL_Renderer* renderer) {

	

}


// shutdown function:

void AssetManager::freeTextures() {

}