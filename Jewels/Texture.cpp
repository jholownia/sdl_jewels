/*
================================
Texture.cpp

Created on: 21 Mar 2014
Author: Jan Holownia

Copyright (c) Jan Holownia <jan.holownia@gmail.com> 2014.

---------------------------------

Description:

See the corresponding header file.

================================
*/

#include "Texture.h"
#include <SDL_image.h>

Texture::Texture(void) :	
	m_texture(nullptr, SDL_DestroyTexture)
{

}

Texture::Texture( std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> &&texture ) :
	m_texture(std::move(texture))
{

}

Texture::~Texture(void)
{

}

bool Texture::init(SDL_Renderer* renderer, const std::string& filename)
{
	bool result = true;

	std::unique_ptr<SDL_Surface, void(*)(SDL_Surface*)> surface(IMG_Load(filename.c_str()), SDL_FreeSurface);

	if (surface != nullptr)
	{
		m_texture.reset(SDL_CreateTextureFromSurface(renderer, surface.get()));
	}
	else
	{
		// std::string error = SDL_GetError();
		result = false;
	}
	
	return result;
}

SDL_Texture* Texture::getTexture() const
{
	return m_texture.get();
}
