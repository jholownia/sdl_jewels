/*
================================
Grid.h

Created on: 21 Mar 2014
Author: Jan Holownia

Copyright (c) Jan Holownia <jan.holownia@gmail.com> 2014.

---------------------------------

Description:

Grid is a helper class responsible for mapping board coordinates
to screen coordinates.
================================
*/
#pragma once

#include <vector>

class Grid
{
public:
	Grid(void);
	Grid(int width, int height, int rows, int cols, int vMargin, int hMargin, int padding);
	~Grid(void);

	void getTileCoords(int position, int& x, int& y) const;

	void getTileSize(int& w, int& h) const;

	int getTileAtCoords(int x, int y) const;

private:	
	std::vector<std::pair<int, int>> m_coords;
	int m_width;
	int m_height;
};

