/*
================================
Game.h

Created on: 21 Mar 2014
Author: Jan Holownia

Copyright (c) Jan Holownia <jan.holownia@gmail.com> 2014.

---------------------------------

Description:

Game class holds the game loop and encapsulates core game functionality.
================================
*/
#pragma once

#include "Config.h"

#include <memory>
#include <vector>
#include <SDL_keycode.h>

class Renderer;
class Board;
class Grid;
class Timer;
class Match;

class Game
{
public:
	Game(void);
	~Game(void);

	bool init(int screenWidth, int screenHeight, int boardWidth, int boardHeight, unsigned int gameTime, int numJewels, int vMargin, int hMargin, int jewelPadding);
	
	int run();

private:
	std::unique_ptr<Renderer> m_renderer;
	std::unique_ptr<Board> m_board;
	std::unique_ptr<Grid> m_grid;
	std::unique_ptr<Timer> m_timer;
	std::unique_ptr<Match> m_match;
	bool m_running;
	int m_selectedJewel;
	Config m_config;

	void update();
	void drawBoard(const std::vector<int>& board);
	void drawSelected();
	void handleMouseClick(int x, int y);
	void handleKeyboardKey(SDL_Keycode keycode);
	void drawSwapAnimation(int pos1, int pos2);
	void drawMatchAnimation(const std::vector<int>& positions);
	void drawWelcomeScreen();
	void drawGameOverScreen();
	void drawScoreAndTime();	
};

