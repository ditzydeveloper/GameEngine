#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "LTexture.h"
#include <map>

class TextureManager
{
private:
	


public:
	TextureManager();
	~TextureManager();

	bool load(std::string filePath, std::string id);

	void draw(std::string id, int x, int y, int w, int h, double scale, double theta, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawFrame(std::string id, int x, int y, int w, int h, int currentRow, int currentFrame, double scale = 1,  double theta =0, SDL_Point* center=nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void render(std::string id, int x, int y, SDL_Rect* clip);

	void setColor(std::string id, Uint8 red, Uint8 green, Uint8 blue);
	void setBlendMode(std::string id, SDL_BlendMode blending);
	void setAlpha(std::string id, Uint8 alpha);

	void deleteTexture(std::string id);
	void setRenderer(SDL_Renderer* renderer);

public:
	//should this be private?
	std::map <std::string, LTexture> textureMap;
	SDL_Renderer* gRenderer = nullptr;
};


typedef TextureManager _TextureManager;
