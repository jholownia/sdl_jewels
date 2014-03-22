/*
================================
Text.cpp

Created on: 21 Mar 2014
Author: Jan Holownia

Copyright (c) Jan Holownia <jan.holownia@gmail.com> 2014.

---------------------------------

Description:

See the corresponding header file.

================================
*/

#include "Text.h"
#include <SDL.h>
#include <SDL_ttf.h>


Text::Text(void) :
	m_texture(nullptr),
	m_font(nullptr, TTF_CloseFont)
{
}

Text::~Text(void)
{
	
}

bool Text::init( const std::string& filename, int size )
{
	bool result = true;

	if (TTF_Init() != 0)
	{
		result = false;
	}

	if (result)
	{	
		m_font.reset(TTF_OpenFont(filename.c_str(), size));		
	}
	
	if(m_font == nullptr)
	{
		result = false;
	}

	return result;
}

SDL_Texture* Text::getTexture() const
{
	return m_texture->getTexture();
}

bool Text::renderToTexture( SDL_Renderer* renderer, const std::string& text )
{
	bool result = true;
		
	SDL_Color color = {250, 250, 250};
	SDL_Color color2 = {0, 0, 0};
	
	std::unique_ptr<SDL_Surface, void(*)(SDL_Surface*)> surface(TTF_RenderText_Blended(m_font.get(), text.c_str(), color), SDL_FreeSurface);

	if (surface != nullptr)
	{
		std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> texture(SDL_CreateTextureFromSurface(renderer, surface.get()), SDL_DestroyTexture);
		m_texture.reset(new Texture(std::move(texture)));
	}
	else
	{
		result = false;
	}

	return result;
}
