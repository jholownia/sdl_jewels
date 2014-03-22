/*
================================
Text.h

Created on: 21 Mar 2014
Author: Jan Holownia

Copyright (c) Jan Holownia <jan.holownia@gmail.com> 2014.

---------------------------------

Description:

Holds a texture with rendered text.
================================
*/

#pragma once

#pragma comment(lib, "SDL2_ttf.lib")

#include "Texture.h"

#include <SDL_ttf.h>

class Text
{
public:
	Text(void);
	~Text(void);
		
	bool init(const std::string& filename, int size);

	bool renderToTexture(SDL_Renderer* renderer, const std::string& text);

	SDL_Texture* getTexture() const;

private:	
	std::unique_ptr<Texture> m_texture;
	std::unique_ptr<TTF_Font, void(*)(TTF_Font*)> m_font;
};

