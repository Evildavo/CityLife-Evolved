#ifndef CITYLIFE_SDL_MANAGERS_H

// Wrapper objects for safely managing the lifetime of SDL components.

namespace CityLife {

	// Exception for SDL errors.
	class SDLError : public std::runtime_error {
	public:
		explicit SDLError(const char* message) : std::runtime_error(message) {}
		explicit SDLError(const std::string& message) : std::runtime_error(message) {}
	};
	
	// Exception for SDL_image errors.
	class IMGError : public SDLError {
	public:
		explicit IMGError(const char* message) : SDLError(message) {}
		explicit IMGError(const std::string& message) : SDLError(message) {}
	};

	// Manages the lifetime of the SDL sub-systems.
	class SystemManager {
	public:
		typedef std::shared_ptr<SystemManager> Ptr;

		SystemManager(Uint32 flags) {
			if (SDL_Init(flags) != 0) {
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

	// Manages the lifetime of the SDL_image loader.
	class ImageLoaderManager {
	public:
		typedef std::shared_ptr<ImageLoaderManager> Ptr;

		ImageLoaderManager(int flags) {
			if (IMG_Init(flags) != flags) {
				std::ostringstream formatter;
				formatter << "IMG_Init Error: " << IMG_GetError() << std::endl;
				throw IMGError(formatter.str());
			}
		}

		~ImageLoaderManager() {
			IMG_Quit();
		}
	};

	// Manages the lifetime of an image loaded from a file.
	class ImageManager {
	public:
		typedef std::shared_ptr<ImageManager> Ptr;

		// Load from file.
		ImageManager(std::string file) {
			surface = IMG_Load(file.c_str());
			if (surface == nullptr) {
				std::ostringstream formatter;
				formatter << "IMG_Load Error: " << IMG_GetError() << std::endl;
				throw IMGError(formatter.str());
			}
		}

		// Allows implicit conversion to SDL_Surface.
		operator SDL_Surface*() const { return surface; }

		~ImageManager() {
			SDL_FreeSurface(surface);
		}

	private:
		SDL_Surface *surface;
	};

	// Manages the lifetime of a texture created from an image.
	class TextureManager {
	public:
		typedef std::shared_ptr<TextureManager> Ptr;

		// Create from an image.
		TextureManager(SDL_Renderer* renderer, SDL_Surface* image) {
			texture = SDL_CreateTextureFromSurface(renderer, image);
			if (texture == nullptr) {
				std::ostringstream formatter;
				formatter << "SDL_CreateTextureFromSurface Error: " << IMG_GetError() << std::endl;
				throw IMGError(formatter.str());
			}
		}

		// Allows implicit conversion to SDL_Texture.
		operator SDL_Texture*() const { return texture; }

		~TextureManager() {
			SDL_DestroyTexture(texture);
		}

	private:
		SDL_Texture *texture;
	};

}

#endif