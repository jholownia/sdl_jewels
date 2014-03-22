/*
================================
main.cpp

Created on: 21 Mar 2014
Author: Jan Holownia

Copyright (c) Jan Holownia <jan.holownia@gmail.com> 2014.

---------------------------------

Description:

Application entry point.

================================
*/

#include "Game.h"

#include <SDL.h>  // remove this somehow

int main(int argc, char* args[])
{
	const int screenWidth = 800;
	const int screenHeight = 600;
	const int boardWidth = 8;
	const int boardHeight = 8;
	const unsigned int gameTime = 60;
	const int numJewels = 5;

	// Board margins
	const int vMargin = 180; 
	const int hMargin = 80;

	const int jewelPadding = 6;
	
	Game game;
	bool result = game.init(screenWidth, screenHeight, boardWidth, boardHeight, gameTime, numJewels, vMargin, hMargin, jewelPadding);

	if (result)
	{
		game.run();	
	}
	
	return 0;
}