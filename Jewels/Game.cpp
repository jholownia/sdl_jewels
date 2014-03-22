/*
================================
Game.cpp

Created on: 21 Mar 2014
Author: Jan Holownia

Copyright (c) Jan Holownia <jan.holownia@gmail.com> 2014.

---------------------------------

Description:

See the corresponding header file.

================================
*/

#include "Game.h"


#include "Renderer.h"
#include "Board.h"
#include "Grid.h"
#include "Timer.h"
#include "Match.h"
#include <SDL.h>
#include <string>


Game::Game(void) :
	m_renderer(nullptr),
	m_board(nullptr),
	m_grid(nullptr),
	m_match(nullptr),
	m_running(false)
{
	
}

Game::~Game(void)
{
}


bool Game::init( const int screenWidth, int screenHeight, int boardWidth, int boardHeight, unsigned int gameTime, int numJewels, int vMargin, int hMargin, int jewelPadding )
{
	m_config.screenWidth = screenWidth;
	m_config.screenHeight = screenHeight;
	m_config.boardWidth = boardWidth;
	m_config.boardHeight = boardHeight;
	m_config.gameTime = gameTime;
	m_config.numJewels = numJewels;
	m_config.vMargin = vMargin;
	m_config.hMargin = hMargin;
	m_config.jewelPadding = jewelPadding;

	bool result = true;

	m_renderer.reset(new Renderer);
	result = m_renderer->init(m_config.screenWidth, m_config.screenHeight, m_config.numJewels);

	if (result)
	{
		m_board.reset(new Board(m_config.boardWidth, m_config.boardHeight));
		m_board->init();

		m_grid.reset(new Grid(m_config.screenWidth, m_config.screenHeight, m_config.boardWidth, m_config.boardHeight, m_config.vMargin, m_config.hMargin, m_config.jewelPadding));

		m_selectedJewel = -1;

		m_timer.reset(new Timer);
		m_timer->start();

		m_match.reset(new Match);
	}	

	return result;
}

int Game::run()
{	
	m_running = true;
	SDL_Event event;

	while(m_running)
	{
		while (SDL_PollEvent(&event) != 0)
		{				
			if (event.type == SDL_QUIT)
			{
				m_running = false;
			}
			else if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					handleMouseClick(event.button.x, event.button.y);
				}
			}
			else if (event.type == SDL_KEYDOWN)
			{
				handleKeyboardKey(event.key.keysym.sym);
			}		
		}

		update();
	}

	return 0;
}

void Game::update()
{	
	m_timer->update();
	
	if (m_match->isStarted())
	{
		m_match->update();		

		m_renderer->beginRender();

		drawBoard(m_board->getBoard());

		if (m_selectedJewel != -1)
		{
			drawSelected();
		}

		drawScoreAndTime();

		m_renderer->endRender();
	}
	else if (m_match->isFinished())
	{
		drawGameOverScreen();
	}
	else
	{
		drawWelcomeScreen();
	}
}

void Game::handleMouseClick( int x, int y )
{	
	int clicked = m_grid->getTileAtCoords(x, y);
	if (clicked != -1)
	{
		if (m_selectedJewel == -1)
		{
			m_selectedJewel = clicked;
		}
		else
		{
			if (m_board->trySwap(m_selectedJewel, clicked))
			{
				drawSwapAnimation(m_selectedJewel, clicked);

				// Check if the move results in a match
				std::vector<int> matches;
				bool matchesFound = false;
				
				if (m_board->checkPosition(m_selectedJewel, matches))
				{
					drawMatchAnimation(matches);
					m_board->removeMatches(matches);
					m_match->updateScore(matches.size());
					
					matchesFound = true;
				}

				if (m_board->getBoard()[clicked] != 0 && m_board->checkPosition(clicked, matches))
				{
					drawMatchAnimation(matches);
					m_board->removeMatches(matches);
					m_match->updateScore(matches.size());

					matchesFound = true;
				}

				if (!matchesFound)
				{
					m_board->trySwap(clicked, m_selectedJewel);
					drawSwapAnimation(clicked, m_selectedJewel);
				}
				else
				{
					m_board->update();
	
					// Keep checking for new matches until we don't have any left
					matches.clear();
					bool moreMatches = true;
	
					while (moreMatches)
					{
						size_t i;
	
						for (i = 0; i < m_board->getBoard().size(); ++i)
						{
							if (m_board->checkPosition(i, matches))
							{
								drawMatchAnimation(matches);
								m_board->removeMatches(matches);
								m_match->updateScore(matches.size());
								m_board->update();
								break;
							}
						}
	
						// If we checked all positions there are no more matches
						if (i == m_board->getBoard().size())
						{
							moreMatches = false;
						}					
					}
				}

				m_selectedJewel = -1;
			}
			else // The jewels are not swappable
			{
				m_selectedJewel = clicked;
			}
		}
	}
}

void Game::handleKeyboardKey( SDL_Keycode keycode )
{
	switch(keycode)
	{
	case SDLK_ESCAPE:
		m_running = false;
		break;
	case SDLK_RETURN:
		if (!m_match->isStarted()) m_match->start(m_config.gameTime);
		break;
	}
}

void Game::drawSwapAnimation( int pos1, int pos2 )
{	
	int x1, x2, y1, y2, w, h;

	m_grid->getTileSize(w, h);
	
	m_grid->getTileCoords(pos2, x1, y1);
	m_grid->getTileCoords(pos1, x2, y2);
	
	// Create a copy of the board for animation
	std::vector<int> brd(m_board->getBoard());
	brd[pos1] = 0;
	brd[pos2] = 0;

	bool vertSwap = (x1 == x2);

	float distance = vertSwap ? (float)std::abs(y1 - y2) : (float)std::abs(x1 - x2);
	int direction = 0;

	if (vertSwap)
	{
		direction = (y2 > y1) ? 1 : -1;
	}
	else
	{
		direction = (x2 > x1) ? 1 : -1;
	}

	float fx1, fx2, fy1, fy2;
	fx1 = (float) x1;
	fx2 = (float) x2;
	fy1 = (float) y1;
	fy2 = (float) y2;

	float movement = 0;

	while(distance > 0)
	{
		m_timer->update();

		m_renderer->beginRender();
		
		drawBoard(brd);
		
		drawScoreAndTime();

		movement = 0.2f * m_timer->getFrameTime();

		distance -= movement;

		if (vertSwap)
		{
			fy1 += movement * direction;
			fy2 -= movement * direction;
		}
		else
		{
			fx1 += movement * direction;
			fx2 -= movement * direction;
		}

		m_renderer->renderJewel(m_board->getBoard()[pos1], (int)fx1, (int)fy1, w, h);
		m_renderer->renderJewel(m_board->getBoard()[pos2], (int)fx2, (int)fy2, w, h);

		m_renderer->endRender();
	}	
}

void Game::drawBoard(const std::vector<int>& board)
{
	int x, y, w, h;

	m_grid->getTileSize(w, h);
	
	for (size_t i = 0; i < board.size(); ++i)
	{
		m_grid->getTileCoords(i, x, y);
		m_renderer->renderJewel(board[i], x, y, w, h);
	}	
}

void Game::drawSelected()
{
	int x, y, w, h;
	
	m_grid->getTileSize(w, h);

	m_grid->getTileCoords(m_selectedJewel, x, y);
	m_renderer->renderHighlightedJewel(m_board->getBoard()[m_selectedJewel], x, y, w, h );	
}

void Game::drawMatchAnimation( const std::vector<int>& positions )
{
	// Create a copy of the board for animation
	std::vector<int> brd(m_board->getBoard());
	
	for (size_t i = 0; i < positions.size(); ++i)
	{
		brd[positions[i]] = 0;
	}

	int w, h, x, y;

	m_grid->getTileSize(w, h);

	float fw = (float)w;
	float fh = (float)h;

	float sizeShift = 0;

	while (fw > 0.1f)
	{
		m_timer->update();

		sizeShift = 0.2f * m_timer->getFrameTime();

		fw -= sizeShift;
		fh -= sizeShift;

		m_renderer->beginRender();

		drawBoard(brd);

		drawScoreAndTime();

		for (size_t i = 0; i < positions.size(); ++i)
		{
			m_grid->getTileCoords(positions[i], x, y);
			x += (w - (int)fw) / 2;
			y += (h - (int)fh) / 2;
			m_renderer->renderJewel(m_board->getBoard()[positions[i]], x, y, (int)fw, (int)fh);
		}

		m_renderer->endRender();
	}

	
}

void Game::drawWelcomeScreen()
{
	int xCenter = m_config.screenWidth / 2;
	int yCenter = m_config.screenHeight / 2;

	int w, h;
	m_grid->getTileSize(w, h);

	m_renderer->beginRender();

	int adjustment = 200;
	int spacer = adjustment / m_config.numJewels;

	for (size_t i = 1; i <= m_config.numJewels; ++i)
	{
		m_renderer->renderJewel(i, xCenter - adjustment + w/2, yCenter + 150, w, h);
		adjustment -= spacer * 2;
	}

	m_renderer->renderText("Welcome to Jewels++!", xCenter - 200, yCenter - 200, 100, 400);
	m_renderer->renderText("Press Enter to start the game or Esc to exit.", xCenter - 230, yCenter, 40, 460);

	m_renderer->endRender();
}

void Game::drawGameOverScreen()
{
	int xCenter = m_config.screenWidth / 2;
	int yCenter = m_config.screenHeight / 2;
	
	int hs;

	std::string str1, str2, str3;

	if (Match::getHighScore(hs))
	{
		str1 = "New High Score!";
		str2 = std::to_string(hs);
	}
	else
	{
		str1 = "Game Over!";
		str2 = std::to_string(m_match->getScore());
	}

	str3 = "Press Enter to play again or Esc to exit.";

	m_renderer->beginRender();
	
	m_renderer->renderText(str1, xCenter - 200, yCenter - 200, 100, 400);
	m_renderer->renderText(str2, xCenter - 50, yCenter - 50, 60, 100);
	m_renderer->renderText(str3, xCenter - 230, yCenter + 50, 40, 460);

	m_renderer->endRender();
}

void Game::drawScoreAndTime()
{
	int xCenter = m_config.screenWidth / 2;
	
	std::string scoreString = "Score: ";
	scoreString.append(std::to_string(m_match->getScore()));

	std::string timeString = "Time: ";
	timeString.append(std::to_string(m_match->timeRemaining()));

	m_renderer->renderText(scoreString, xCenter - 200 - 60, 10, 60, 100);
	m_renderer->renderText(timeString, xCenter + 200 - 60, 10, 60, 100);
}
