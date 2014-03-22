/*
================================
Texture.h

Created on: 21 Mar 2014
Author: Jan Holownia

Copyright (c) Jan Holownia <jan.holownia@gmail.com> 2014.

---------------------------------

Description:

Holds a texture.
================================
*/

#pragma once

#pragma comment(lib, "SDL2_image.lib")

#include <memory>
#include <string>
#include <SDL.h>

class Texture
{
public:
	Texture(void);
	Texture(std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> &&texture);
	~Texture(void);

	virtual bool init(SDL_Renderer* renderer, const std::string& filename);
	
	SDL_Texture* getTexture() const;

protected:	
	std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> m_texture;
};

