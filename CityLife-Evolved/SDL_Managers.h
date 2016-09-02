#ifndef CITYLIFE_SDL_MANAGERS_H

// Wrapper objects for safely managing the lifetime of SDL components.

namespace CityLife {

	// Exception for SDL errors.
	class SDLError : public std::runtime_error {
	public:
		explicit SDLError(const char* message) : std::runtime_error(message) {}
		explicit SDLError(const std::string& message) : std::runtime_error(message) {}
	};

	// Manages the lifetime of the SDL sub-systems.
	class SystemManager {
	public:
		typedef std::shared_ptr<SystemManager> Ptr;

		SystemManager(Uint32 flags) {
			if (SDL_Init(SDL_INIT_VIDEO) != 0) {
				std::ostringstream formatter;
				formatter << "SDL_Init Error: " << SDL_GetError() << std::endl;
				throw SDLError(formatter.str());
			}
		}

		~SystemManager() {
			SDL_Quit();
		}
	};

	// Manages the lifetime of an SDL window.
	class WindowManager {
	public:
		typedef std::shared_ptr<WindowManager> Ptr;

		WindowManager(
			const char *title, int x, int y, int w, int h, Uint32 flags)
		{
			win = SDL_CreateWindow(title, x, y, w, h, flags);
			if (win == nullptr) {
				std::ostringstream formatter;
				formatter << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
				throw SDLError(formatter.str());
			}
		}

		// Allows implicit conversion to SDL_Window.
		operator SDL_Window*() const { return win; }

		~WindowManager() {
			SDL_DestroyWindow(win);
		}

	private:
		SDL_Window *win;
	};

	// Manages the lifetime of an SDL renderer.
	class RenderManager {
	public:
		typedef std::shared_ptr<RenderManager> Ptr;

		RenderManager(
			SDL_Window * window, int index, Uint32 flags)
		{
			ren = SDL_CreateRenderer(window, index, flags);
			if (ren == nullptr) {
				std::ostringstream formatter;
				formatter << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
				throw SDLError(formatter.str());
			}
		}

		// Allows implicit conversion to SDL_Renderer.
		operator SDL_Renderer*() const { return ren; }

		~RenderManager() {
			SDL_DestroyRenderer(ren);
		}

	private:
		SDL_Renderer *ren;
	};

}

#endif