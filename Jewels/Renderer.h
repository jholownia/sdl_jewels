/*
================================
Renderer.h

Created on: 21 Mar 2014
Author: Jan Holownia

Copyright (c) Jan Holownia <jan.holownia@gmail.com> 2014.

---------------------------------

Description:

Renderer encapsulates all rendering functionality and resources.
================================
*/

#pragma once

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")

#include <memory>
#include <array>
#include <vector>

struct SDL_Window;
struct SDL_Surface;
struct SDL_Renderer;
class Texture;
class Text;

class Renderer
{
public:
	Renderer(void);
	~Renderer(void);

	bool init(int width, int height, int numJewels);	

	void renderJewel(int jewel, int x, int y, int h, int w);

	void renderHighlightedJewel(int jewel, int x, int y, int h, int w);

	void renderText(const std::string& text, int x, int y, int h, int w );
	
	void beginRender();

	void endRender();

private:
	std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> m_window;
	std::unique_ptr<SDL_Surface, void(*)(SDL_Surface*)> m_surface;
	std::vector<std::unique_ptr<Texture>> m_sprites;	
	std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> m_renderer;
	std::unique_ptr<Text> m_text;

	bool loadAssets(int numTextures);
};

