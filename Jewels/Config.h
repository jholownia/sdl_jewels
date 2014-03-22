/*
================================
Config.h

Created on: 21 Mar 2014
Author: Jan Holownia

Copyright (c) Jan Holownia <jan.holownia@gmail.com> 2014.

---------------------------------

Description:

A structure to hold some configuration variables.
================================
*/

#pragma once

struct Config
{
	int screenWidth;
	int screenHeight;
	int boardWidth;
	int boardHeight;
	unsigned int gameTime;
	int numJewels;
	int vMargin;
	int hMargin;
	int jewelPadding;
};