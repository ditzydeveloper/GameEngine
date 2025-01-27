#include <iostream>
#include <iomanip>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>
#include "LTexture.h"
#include "Game.h"

#define SDL_MAIN_HANDLED
using namespace std;

int main(int argc, char* argv[]) {

	srand(time(NULL));
	Game game;


	if (!game.init()) {
		printf("Failed to initialize assets!\n");
	}

	game.processEvents();

	game.shutdown();

	return 0;
}