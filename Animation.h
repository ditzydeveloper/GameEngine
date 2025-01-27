#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>


class Animation
{

private:
	std::string textureID;
	std::vector<SDL_Rect*> aFrames;
	int currentFrame = 0;
	float frameSpeed;
	float elapsedTime = 0;

public:

	Animation(std::string ID, float fSpeed) : textureID(ID), frameSpeed(fSpeed) {};
	~Animation();
	void addFrame(const SDL_Rect& frame);
	void update(int deltaTime);
	std::string getTextureID();
	SDL_Rect* getCurrentFrame();

};

