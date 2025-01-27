#include "Animation.h"
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <iostream>





Animation::~Animation() {

}


void Animation::addFrame(const SDL_Rect& frame) {
	aFrames.push_back(new SDL_Rect(frame)); // Dynamically allocate and copy the frame
}


void Animation::update(int deltaTime) {
	elapsedTime += deltaTime;
	std::cout << "elapsedTime: " << elapsedTime << std::endl;
	std::cout << "deltaTime: " << deltaTime << std::endl;

	if (elapsedTime >= frameSpeed) {
		elapsedTime = 0;
		currentFrame = (currentFrame + 1) % aFrames.size();
	}
}


std::string Animation::getTextureID() {
	return textureID;
}


SDL_Rect* Animation::getCurrentFrame() {
	std::cout << "current Frame: " << currentFrame << std::endl;
	return aFrames[currentFrame];
}
