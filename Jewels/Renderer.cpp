/*
================================
Renderer.cpp

Created on: 21 Mar 2014
Author: Jan Holownia

Copyright (c) Jan Holownia <jan.holownia@gmail.com> 2014.

---------------------------------

Description:

See the corresponding header file.

================================
*/


#include "Renderer.h"
#include "Texture.h"
#include "Text.h"

#include <SDL.h>
#include <SDL_ttf.h>


Renderer::Renderer(void) :
	m_window(nullptr, SDL_DestroyWindow),
	m_surface(nullptr, SDL_FreeSurface),
	m_renderer(nullptr, SDL_DestroyRenderer),
	m_text(nullptr)	
{

}

Renderer::~Renderer(void)
{
	
}

bool Renderer::init(int width, int height, int numJewels)
{
	bool result = true;
		
	result = (SDL_Init(SDL_INIT_VIDEO) == 0);

	if (result)
	{		
		m_window.reset(SDL_CreateWindow("Jewels", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN));

		if (m_window != nullptr)
		{
			m_surface.reset(SDL_GetWindowSurface(m_window.get()));

			SDL_FillRect(m_surface.get(), NULL, SDL_MapRGB(m_surface->format, 0, 0, 0));
			SDL_UpdateWindowSurface(m_window.get());

			// Renderer
			m_renderer.reset(SDL_CreateRenderer(m_window.get(), -1, SDL_RENDERER_ACCELERATED));
			if (m_renderer != nullptr)
			{
				SDL_SetRenderDrawColor(m_renderer.get(), 0, 0, 0, 0);
			}
			else
			{
				result = false;				
			}
		}
		else
		{
			result = false;
		}
	}

	if (result)
	{
		result = loadAssets(numJewels);
	}
	
	return result;
}

void Renderer::renderJewel( int jewel, int x, int y, int h, int w )
{
	if (jewel != 0)
	{
		SDL_Rect targetRect;
		targetRect.x = x;
		targetRect.y = y;
		targetRect.w = w;
		targetRect.h = h;
	
		SDL_RenderCopy(m_renderer.get(), m_sprites[jewel - 1]->getTexture(), NULL, &targetRect);
	}
}

void Renderer::renderHighlightedJewel( int jewel, int x, int y, int h, int w )
{
	jewel += 5;
	renderJewel( jewel, x, y, h, w );
}

void Renderer::renderText( const std::string& text, int x, int y, int h, int w )
{
	if (text != "")
	{
		SDL_Rect targetRect;
		targetRect.x = x;
		targetRect.y = y;
		targetRect.w = w;
		targetRect.h = h;

		m_text->renderToTexture(m_renderer.get(), text);

		SDL_RenderCopy(m_renderer.get(), m_text->getTexture(), NULL, &targetRect);
	}
}

void Renderer::beginRender()
{
	SDL_RenderClear(m_renderer.get());
}

void Renderer::endRender()
{
	SDL_RenderPresent(m_renderer.get());
}

bool Renderer::loadAssets( int numTextures )
{
	bool result = true;

	// Load all textures
	m_sprites.resize(numTextures * 2);
	m_sprites[0] = std::unique_ptr<Texture>(new Texture);
	result = m_sprites[0]->init(m_renderer.get(), "assets/Red.png");
	m_sprites[1] = std::unique_ptr<Texture>(new Texture);
	result = m_sprites[1]->init(m_renderer.get(), "assets/Green.png");
	m_sprites[2] = std::unique_ptr<Texture>(new Texture);
	result = m_sprites[2]->init(m_renderer.get(), "assets/Blue.png");
	m_sprites[3] = std::unique_ptr<Texture>(new Texture);
	result = m_sprites[3]->init(m_renderer.get(), "assets/Purple.png");	
	m_sprites[4] = std::unique_ptr<Texture>(new Texture);
	result = m_sprites[4]->init(m_renderer.get(), "assets/Yellow.png");

	m_sprites[5] = std::unique_ptr<Texture>(new Texture);
	result = m_sprites[5]->init(m_renderer.get(), "assets/Red_glow.png");
	m_sprites[6] = std::unique_ptr<Texture>(new Texture);
	result = m_sprites[6]->init(m_renderer.get(), "assets/Green_glow.png");
	m_sprites[7] = std::unique_ptr<Texture>(new Texture);
	result = m_sprites[7]->init(m_renderer.get(), "assets/Blue_glow.png");
	m_sprites[8] = std::unique_ptr<Texture>(new Texture);
	result = m_sprites[8]->init(m_renderer.get(), "assets/Purple_glow.png");	
	m_sprites[9] = std::unique_ptr<Texture>(new Texture);
	result = m_sprites[9]->init(m_renderer.get(), "assets/Yellow_glow.png");

	// Init text
	m_text.reset(new Text);
	result = m_text->init("assets/brd.ttf", 80);

	return result;
}

