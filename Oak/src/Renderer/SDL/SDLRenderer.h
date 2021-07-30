#pragma once
#include "src/Renderer/Renderer.h"
#include "SDL.h"
#include <src/Renderer/SDL/SDLWindow.h>
#include <iostream>
namespace Oak
{
	class SDLRenderer : public Renderer
	{
	public:
		SDLRenderer(SDLWindow* window)
		{
			this->window = window;
			renderer = NULL;
		}
		~SDLRenderer()
		{
			SDL_DestroyRenderer(renderer);
			SDL_Quit();
		}
		bool Init() override
		{
			SDL_Init(SDL_INIT_EVERYTHING);
			renderer = SDL_CreateRenderer(window->Instance(), -1, SDL_RENDERER_ACCELERATED);

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

			SDL_RenderClear(renderer);
			SDL_RenderPresent(renderer);
			return true;
		}
		void BeginFrame() override
		{
			//Set the renderer color.
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

			//Clear the renderer.
			SDL_RenderClear(renderer);
		}
		void EndFrame() override
		{
			SDL_RenderPresent(renderer);
		}
		void DrawQuad(f32 x, f32 y, f32 w, f32 h, i32 r, i32 g, i32 b, i32 a) override
		{
			SDL_Rect rect = { x, y, w, h };
			SDL_SetRenderDrawColor(renderer, r, g, b, a);
			SDL_RenderFillRect(renderer, &rect);
		}
	private:
		SDLWindow* window;
		SDL_Renderer* renderer;
	};
}