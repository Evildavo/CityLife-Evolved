#include "pch.h"
#include "SDL_Managers.h"

using namespace CityLife;


// Entry point.
int main(int argc, char *args[]) {
	const std::string ERROR_LOG = "ErrorLog.txt";

	// Reset the log.
	remove(ERROR_LOG.c_str());

	// Initialise SDL and create a window.
	SystemManager::Ptr system;
	WindowManager::Ptr window;
	RenderManager::Ptr render;
	try {
		system = SystemManager::Ptr(new SystemManager(SDL_INIT_VIDEO));
		window = WindowManager::Ptr(
			new WindowManager("Hello World!",
					SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
					1024, 640, SDL_WINDOW_SHOWN
				)
			);
		render = RenderManager::Ptr(
			new RenderManager(*window, -1,
					SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
				)
			);
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

	//A sleepy rendering loop, wait for 3 seconds and render and present the screen each time
	for (int i = 0; i < 3; ++i) {
		SDL_RenderClear(*render);
		SDL_RenderPresent(*render);
		SDL_Delay(1000);
	}
	return 0;
}
