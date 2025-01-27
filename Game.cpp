#include "Game.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <chrono>
#include "Animation.h"
using namespace std;



Game::Game() {


} 

Game::~Game() {
	shutdown();
}

bool Game::init() {
	gWindow.init();
	gAssets.setRenderer(gWindow.getRenderer());
	bool success = gAssets.loadMedia();
	return success;
}


Animation Game::initAnimation() {
	Animation walkAnimation("test", 5);

	walkAnimation.addFrame(SDL_Rect{ 0, 0, 64, 205 });
	walkAnimation.addFrame(SDL_Rect{ 64, 0, 64, 205 });
	walkAnimation.addFrame(SDL_Rect{ 128, 0, 64, 205 });
	walkAnimation.addFrame(SDL_Rect{ 192, 0, 64, 205 });

	return walkAnimation;
}

void Game::processEvents() {

	SDL_Event event;
	bool quit = false;
	//modulation components
	Uint8 r = 255;
	Uint8 g = 255;
	Uint8 b = 255;
	Uint8 a = 255;

	Animation walkAnimation = initAnimation();

	float lastTick = SDL_GetTicks() / 10.0f;;
	float deltaTime = 0;
	float currentTick = 0;

	while (!quit) {
		std::cout << "lasttick " << lastTick << std::endl;
		
		//check for events
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT: //SDL_QUIT event (which is the event when the user Xs out the window),
				quit = true;
				break;
			case SDL_MOUSEMOTION:
				cout << "Hello";
			case SDL_KEYDOWN:
				switch( event.key.keysym.sym ){
					//Increase red
				case SDLK_q:
					r += 32;
					break;

					//Increase green
				case SDLK_w:
					g += 32;
					break;

					//Increase blue
				case SDLK_e:
					b += 32;
					break;

					//Decrease red
				case SDLK_a:
					r -= 32;
					break;

					//Decrease green
				case SDLK_s:
					g -= 32;
					break;

					//Decrease blue
				case SDLK_d:
					b -= 32;
					break;
				}
			}
		}


		//clear Screen with color
		SDL_SetRenderDrawColor(gAssets.textureManager.gRenderer, 0xff, 0xff, 0xff, 0xff);
		if (SDL_RenderClear(gAssets.textureManager.gRenderer)) {
			std::cerr << "SDL_RenderClear Error: " << SDL_GetError() << std::endl;
		}

		gAssets.textureManager.setColor("test", r, g, b);

		//gAssets.textureManager.textureMap["test"].render(0, 0, gAssets.textureManager.gRenderer, &gAssets.mSpriteClips[0]);
		//gAssets.textureManager.textureMap["test"].render(gWindow.SCREEN_WIDTH - gAssets.mSpriteClips[1].w, 0, gAssets.textureManager.gRenderer, &gAssets.mSpriteClips[1]);
		//gAssets.textureManager.textureMap["test"].render(0, gWindow.SCREEN_HEIGHT - gAssets.mSpriteClips[2].h, gAssets.textureManager.gRenderer, &gAssets.mSpriteClips[2]);
		//gAssets.textureManager.textureMap["test"].render(gWindow.SCREEN_WIDTH - gAssets.mSpriteClips[3].w, gWindow.SCREEN_HEIGHT - gAssets.mSpriteClips[3].h, gAssets.textureManager.gRenderer, &gAssets.mSpriteClips[3]);

		

		gAssets.textureManager.render("test", gWindow.SCREEN_WIDTH /2,
												 gWindow.SCREEN_HEIGHT /2 ,
												 walkAnimation.getCurrentFrame());
		//gAssets.textureManager.drawFrame("test", gWindow.SCREEN_WIDTH - 100, 0, 100, 100, 1, 0, 0, 0);
		//gAssets.textureManager.drawFrame("test", 0, 0, 100, 100, 1, 0, 1, 0);

		SDL_RenderPresent(gAssets.textureManager.gRenderer);  // update screen


		walkAnimation.update(deltaTime);

		currentTick = SDL_GetTicks() / 10.0f; // Convert milliseconds to seconds
		deltaTime = (currentTick - lastTick);
		lastTick = currentTick;

		
		
	}
}

void Game::update() {

}

float Game::getTick() {
	auto now = std::chrono::steady_clock::now(); // Use steady_clock for monotonic behavior
	auto duration = now.time_since_epoch();
	auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
	return static_cast<float>(milliseconds.count()); // Explicitly cast to float
}


void Game::shutdown() {
	gAssets.freeTextures();
	gWindow.SDL_cleanUp();

}
