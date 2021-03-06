#include "pch.h"
#include "Managers.h"
#include "TileMap.h"

using namespace CityLife;


// Entry point.
int main(int argc, char *args[]) {
	const std::string ERROR_LOG = "ErrorLog.txt";

	// Reset the log.
	remove(ERROR_LOG.c_str());
	
	// Initialise.
	SystemManager::Ptr system;
	WindowManager::Ptr window;
	RenderManager::Ptr renderer;
	ImageLoaderManager::Ptr imageLoader;
	TextureManager::Ptr cellTexture;
	try {
		
		// Initialise SDL systems and create a window.
		system = SystemManager::Ptr(new SystemManager(SDL_INIT_VIDEO));
		window = WindowManager::Ptr(
			new WindowManager("CityLife-Evolved",
					SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
					1024, 640, SDL_WINDOW_SHOWN
				)
			);
		renderer = RenderManager::Ptr(
			new RenderManager(*window, -1,
					SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
				)
			);
		imageLoader = ImageLoaderManager::Ptr(new ImageLoaderManager(IMG_INIT_PNG));

		// Load assets.
		ImageManager image("Assets/Cells.png");
		cellTexture = TextureManager::Ptr(new TextureManager(*renderer, image));
	}
	catch (SDLError& e) {
		std::ofstream out(ERROR_LOG);
		if (out) {
			out << e.what();
			out.close();
		}
		std::cout << e.what();
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Fatal Error", e.what(), NULL);
		return 1;
	}

	// Set up game objects.
	TileMap tileMap(*cellTexture, 16, 16, 20, 12);
	TileMap::Index houseTile = tileMap.getIndex(0, 1);
	TileMap::Index roadTile = tileMap.getIndex(1, 2);
	tileMap.setTile(0, 0, houseTile);
	tileMap.setTile(10, 10, houseTile);
	tileMap.setTile(6, 5, roadTile);
	tileMap.setTile(7, 5, roadTile);
	tileMap.setTile(8, 5, roadTile);

	// Main loop.
	bool quit = false;
	SDL_Event event;
	while (!quit) {

		// Handle events.
		SDL_WaitEvent(&event);
		switch (event.type) {
		case SDL_QUIT:
			quit = true;
			break;
		}

		// Draw scene.
		SDL_RenderClear(*renderer);
		tileMap.render(*renderer, 50, 50, 3);
		SDL_RenderPresent(*renderer);
	}
	return 0;
}
