#include "GameWindow.h"
#include "iostream";
#include  <SDL.h>
#include <SDL_image.h>
#define SDL_MAIN_HANDLED

using namespace std;

GameWindow::GameWindow() {

	m_window = SDL_CreateWindow("GAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (m_window == NULL) {
		SDL_Quit();
	}
	else {
		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
		if (m_renderer == NULL) {
			printf("Renderer could not be created . SDL Error: %s\n", SDL_GetError());
		}
		else {

			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags)) {
				printf("SDL_image could not initalize!  SDL_image Error: %s\n", IMG_GetError());
			}
		}
	};

	 // m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
	// m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);

	// if (m_texture == NULL) {
	// 	cout << "could not create texture";
	// 	SDL_DestroyRenderer(m_renderer);
	// 	SDL_DestroyWindow(m_window);
	//}

	m_buffer = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
};


bool GameWindow::loadMedia() {

	bool success = true;


	//load default surface
	m_KeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] = loadSurface("C:\\Users\\McAll\\OneDrive\\Documents\\silly pup.bmp");
	if (m_KeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == nullptr) {
		printf("Failed to load default image!\n");
		success = false;
	}

	//load up surface
	m_KeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("C:\\Users\\McAll\\OneDrive\\Pictures\\Saved Pictures\\png image.png");
	if (m_KeyPressSurfaces[KEY_PRESS_SURFACE_UP] == nullptr) {
		printf("Failed to load up image!\n");
		success = false;
	}

	//load Down surface
	m_KeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("C:\\Users\\McAll\\Documents\\down.bmp");
	if (m_KeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == nullptr) {
		printf("Failed to load down image!\n");
		success = false;
	}

	//load left surface
	m_KeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("C:\\Users\\McAll\\Documents\\left.bmp");
	if (m_KeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == nullptr) {
		printf("Failed to load LEFT image!\n");
		success = false;
	}

	//load RIGHT surface
	m_KeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("C:\\Users\\McAll\\Documents\\right.bmp");
	if (m_KeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == nullptr) {
		printf("Failed to load RIGHT image!\n");
		success = false;
	}

	return success;
};


bool GameWindow::loadMedia_texture() {

	bool success = true;
	m_texture = loadTexture("C:\\Users\\McAll\\OneDrive\\Pictures\\Saved Pictures\\png image.png");
	if (m_texture == nullptr) {
		printf("Failed to load texutre image!");
		success = false;
	}
	return success;
};

GameWindow::~GameWindow() {

};

bool GameWindow::init() {
	SDL_Start();
	memset(m_buffer, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32)); // sets memory with a specified value
	m_buffer[3000] = 0xFFFFFFFF; //each pixel occupies one byte

	// Lazy Foo's code:

	m_screenSurface = SDL_GetWindowSurface(m_window);
	return 0;
};


void GameWindow::update() {
	SDL_UpdateTexture(m_texture, //first param, the texture
		NULL,
		m_buffer,
		SCREEN_WIDTH * sizeof(Uint32)  // pitch - amount of pixels in each row
	);
};

void GameWindow::clear() {
	memset(m_buffer, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
};



// def need to spend more time studying how this works 
void GameWindow::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {  // is inefficent to check every single pixel we plot if its in screen range. but oh well.
		return;
	}
	Uint32 color = 0;

	// bit shift, shift the bits down 8 in the byte.
	color += red;
	color <<= 8;
	color += green;
	color <<= 8;
	color += blue;
	color <<= 8;
	color += 0xFF;

	m_buffer[(y * SCREEN_WIDTH) + x] = color;  // (y * SCREEN_WIDTH) + x, convertrs x, y corrdiants to the Uint32 

};


SDL_Surface* GameWindow::loadSurface(std::string path) {

	SDL_Surface* optimizedSurface = nullptr;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr) {
		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	}
	else {
		optimizedSurface = SDL_ConvertSurface(loadedSurface, m_screenSurface->format, 0);
		if (optimizedSurface == nullptr) {
			printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		// get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	return optimizedSurface;
};

SDL_Texture* GameWindow::loadTexture(std::string path) {
	SDL_Texture* newTexture = nullptr;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else {
		newTexture = SDL_CreateTextureFromSurface(m_renderer, loadedSurface);
		if (newTexture == nullptr) {
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
};


// def need to spend more time studying how this works 
bool GameWindow::processEvents() {
	SDL_Event event;
	bool quit = false;

	m_currentSurface = m_KeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
	while (!quit) {
		// update pixel
		//draw pixel 
		//check for events
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT: //SDL_QUIT event (which is the event when the user Xs out the window),
				quit = true;
			case SDL_MOUSEMOTION:
				cout << "Hello";
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_UP:
					m_currentSurface = m_KeyPressSurfaces[KEY_PRESS_SURFACE_UP];
					break;
				case SDLK_DOWN:
					m_currentSurface = m_KeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
					break;
				case SDLK_LEFT:
					m_currentSurface = m_KeyPressSurfaces[KEY_PRESS_SURFACE_LEFT]; 
					break;
				case SDLK_RIGHT:
					m_currentSurface = m_KeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
					break;
				default:
					m_currentSurface = m_KeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
					break;
				}
			}
		}

		SDL_Rect stretchRect;
		stretchRect.x = 0;
		stretchRect.y = 0;
		stretchRect.w = SCREEN_WIDTH;
		stretchRect.h = SCREEN_HEIGHT;


		SDL_RenderClear(m_renderer);  //clear Screen
		SDL_RenderCopy(m_renderer, m_texture, NULL, NULL); // render texture to screen
		SDL_RenderPresent(m_renderer);  // update screen

		//SDL_BlitScaled(m_currentSurface, NULL, m_screenSurface, &stretchRect);
		//Update the surface
		//SDL_UpdateWindowSurface(m_window);

	}
	return 0;
};

bool GameWindow::processEvents_shapes() {
	SDL_Event event;
	bool quit = false;

	m_currentSurface = m_KeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
	SDL_SetRenderDrawColor(m_renderer, 0xff, 0xff, 0xff, 0xff);
	SDL_RenderClear(m_renderer);


	// red rectangle
	SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	SDL_SetRenderDrawColor(m_renderer, 0xff, 0x00, 0x00, 0xff);
	SDL_RenderFillRect(m_renderer, &fillRect);
	//Render green outlined quad
	SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
	SDL_SetRenderDrawColor(m_renderer, 0x00, 0xFF, 0x00, 0xFF);
	SDL_RenderDrawRect(m_renderer, &outlineRect);

	//Draw blue horizontal line
	SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0xFF, 0xFF);
	SDL_RenderDrawLine(m_renderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);

	//Draw vertical line of yellow dots
	SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0x00, 0xFF);

	
	for (int i = 0; i < SCREEN_HEIGHT; i += 4)
	{
		SDL_RenderDrawPoint(m_renderer, SCREEN_WIDTH / 2, i);
	}
	SDL_RenderPresent(m_renderer);
	while (!quit)
	{
		while (SDL_PollEvent(&event) != 0) {
			switch (event.type) {
			case SDL_QUIT: //SDL_QUIT event (which is the event when the user Xs out the window),
				quit = true;
			case SDL_MOUSEMOTION:
				cout << "Hello";
			}
		}
	};
	return 0;
};


// init method for sdl
void GameWindow::SDL_Start() {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
		cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return; // Exit or handle the error appropriately
	}
	else {
		return;
	}
};

//clean up at close down
void GameWindow::SDL_cleanUp() {
	delete[] m_buffer;
	SDL_FreeSurface(m_image);
	m_image = NULL;
	SDL_DestroyTexture(m_texture);
	m_texture = nullptr;
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
};