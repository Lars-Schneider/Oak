#pragma once
#include "SDL.h"
namespace Oak
{
	class SDLWindow
	{
	public:
		SDLWindow()
		{

		}
		~SDLWindow()
		{
			SDL_DestroyWindow(window);
		}
		bool Create(const char* title, int x, int y, int w, int h)
		{
			width = w;
			height = h;
			window = SDL_CreateWindow(title, x, y, w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
			should_close = false;
			return true;
		}
		SDL_Window* Instance()
		{
			return window;
		}
		void PollEvents()
		{
			SDL_Event event;
			while (SDL_PollEvent(&event) != 0)
			{
				switch (event.type)
				{
				case SDL_QUIT:
					should_close = true;
					break;
				case SDL_WINDOWEVENT:
					SDL_GetWindowSize(window, &width, &height);
					break;
				}
			}
		}
		bool Should_Close() { return should_close; }
		int Width()
		{
			return width;
		}
		int Height()
		{
			return height;
		}
	private:
		SDL_Window* window;
		bool should_close;
		int width;
		int height;
	};
}