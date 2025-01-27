#pragma once
#include <iostream>
#include <SDL.h>
#include "LTexture.h"
#include "TextureManager.h"

class AssetManager
{
private:
	


public:
	AssetManager();
	~AssetManager();


	//management function
	bool loadMedia();
	void setRenderer(SDL_Renderer* renderer);


	// init function
	void initManagmentSystems(TextureManager textureM, SDL_Renderer* renderer);

	/// shutdown function
	void freeTextures();
	

public:
	TextureManager textureManager;
	SDL_Rect mSpriteClips[4];

};

