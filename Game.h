#pragma once
#include "Animation.h"
#include <SDL.h>
#include <iostream>
#include <chrono>
#include "LTexture.h"
#include "AssetManager.h"
#include "WindowManager.h"




class Game
{



private:
	WindowManager gWindow;
	AssetManager gAssets;  
	


public:
	Game();
	~Game();
	bool init();
	void processEvents();
	void update();
	void shutdown();
	Animation initAnimation();
	float getTick();



};

