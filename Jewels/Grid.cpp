/*
================================
Grid.cpp

Created on: 21 Mar 2014
Author: Jan Holownia

Copyright (c) Jan Holownia <jan.holownia@gmail.com> 2014.

---------------------------------

Description:

See the corresponding header file.

================================
*/

#include "Grid.h"


Grid::Grid(void)
{

}

Grid::Grid( int width, int height, int rows, int cols, int vMargin, int hMargin, int padding ) :	
	m_coords(width * height)
{
	int x = 0;
	int y = 0;

	for (size_t i = 0; i < m_coords.size(); ++i)
	{
		x = vMargin + ((width - 2 * vMargin) / cols) *  (i % rows) + padding;
		y = hMargin + ((height - 2 * hMargin) / cols) *  (i / cols) + padding;

		m_coords[i] = std::make_pair(x, y);
	}

	int w = width - 2 * vMargin;
	int h = height - 2 * hMargin;
	int unpaddedWidth = w / cols;
	int unpaddedHeight = h / rows;
	m_width = unpaddedWidth - 2 * padding;
	m_height = unpaddedHeight - 2 * padding;
}


Grid::~Grid(void)
{

}

void Grid::getTileCoords( int position, int& x, int& y ) const
{
	if (position < m_coords.size())
	{
		x = m_coords[position].first;
		y = m_coords[position].second;
	}
}

void Grid::getTileSize( int& w, int& h ) const
{
	w = m_width;
	h = m_height;
}

int Grid::getTileAtCoords( int x, int y ) const
{	
	int tile = -1;

	for (size_t i = 0; i < m_coords.size(); ++i)
	{
		if (x > m_coords[i].first && x <= m_coords[i].first + m_width && y > m_coords[i].second && y <= m_coords[i].second + m_height)
		{
			tile = i;
			break;
		}
	}

	return tile;
}
