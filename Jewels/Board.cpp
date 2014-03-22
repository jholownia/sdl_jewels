/*
================================
Board.cpp

Created on: 21 Mar 2014
Author: Jan Holownia

Copyright (c) Jan Holownia <jan.holownia@gmail.com> 2014.

---------------------------------

Description:

See the corresponding header file.

================================
*/

#include "Board.h"

#include <ctime>
#include <iostream>
#include <list>
#include <array>

Board::Board(int rows, int columns) :
	m_rows(rows),
	m_columns(columns),
	m_generator(static_cast<unsigned int>(std::time(0))),
	m_board(rows * columns, 0)
{
	
}


Board::~Board(void)
{

}

void Board::init()
{
	// Fill the board with random jewels
	for (size_t i = 0; i < m_board.size(); ++i)
	{
		m_board[i] = generateRandomJewel();

		// For every third jewel, make sure it's different from the previous three
		if (i % 3 == 2)
		{
			while (m_board[i] == m_board[i-1])
			{
				m_board[i] = generateRandomJewel();
			}
		}
	}

	// Now we know there are no horizontal matches, we need to check for vertical
	// It's enough if we check every second row
	std::vector<int> matches;

	for (size_t i = m_columns; i < m_board.size(); ++i)
	{
		if (findVerticalMatches(i, matches))
		{
			// Change every 3rd element so it doesn't match others
			for (size_t j = 0; j < matches.size(); ++j)
			{
				if(j % 3 == 2)
				{
					int k = matches[j];

					if (k == 0 || k == m_board.size() - 1)
					{
						k = matches[j-1];
					}
					
					while(m_board[k] == m_board[k-1] && m_board[k] == m_board[k+1] && m_board[k] == m_board[k-m_columns])
					{
						m_board[i] = generateRandomJewel();
					}
				}
			}
		}

		// Skip one row
		if (isFirstColumn(i))
		{
			i += m_columns;
		}
	}

	// Make sure there are some possible moves on the board
	int pos;
	int swap;

	for (size_t i = 0; i < 2; ++i) // change 2 to m_difficulty
	{
		pos = generateRandomPosition();
		swap = generateRandomSwap(pos);
		
		if (swap == pos - m_columns || swap == pos + m_columns)
		{
			m_board[pos - 1] = m_board[pos];
			m_board[pos + 2] = m_board[pos];
			doSwap(pos, swap);
		}
		else
		{
			m_board[pos - m_columns] = m_board[pos];
			m_board[pos + m_columns] = m_board[pos];
			doSwap(pos, swap);
		}
	}

	// Validate and remove any remaining matches
	for (size_t i = 0; i < m_board.size(); ++i)
	{
		matches.clear();

		while (checkPosition(i, matches))
		{
			for (size_t j = 0; j < matches.size(); ++j)
			{
				if (j % 2 == 0)
				{				
					m_board[matches[j]] = generateRandomJewel();
				}
			}
		}
	}
}

void Board::update()
{
	// First shift all the jewels down to fill empty spaces	
	for (size_t i = 0; i < m_columns; ++i)
	{
		for (size_t j = m_rows - 1; j > 0; --j)
		{			
			int pos = (j * m_columns) + i;
			int swap = pos;
	
			if (m_board[pos] == 0)
			{			
				while (swap >= m_columns)
				{
					if (m_board[swap - m_columns] == 0)
					{
						swap -= m_columns;
						continue;
					}

					doSwap(pos, swap - m_columns);
					break;
				}							
			}		
		}
	}

	// Now generate some new jewels randomly
	for (size_t i = 0; i < m_board.size(); ++i)
	{
		if (m_board[i] == 0)
		{
			m_board[i] = generateRandomJewel();
		}
	}
}

void Board::reset()
{

}

bool Board::findMatches()
{
	bool matchesFound = false;
	
	// Find matches in rows	
	for (size_t i = 0; i < m_rows; ++i)
	{
		for (size_t j = 0; j < m_columns; ++i)
		{
			
		}
	}

	// Find matches in columns
	for (size_t i = 0; i < m_rows; ++i)
	{
		for (size_t j = 0; j < m_columns; ++i)
		{

		}
	}

	return matchesFound;
}

int Board::generateRandomJewel()
{	
	std::uniform_int_distribution<int> distribution(1, 5);

	return distribution(m_generator);
}

int Board::generateRandomPosition()
{
	std::uniform_int_distribution<int> distribution(m_columns + 1, m_board.size() - m_columns - 2);

	int position = distribution(m_generator);

	if (isFirstColumn(position))
	{
		++position;
	}
	else if (isLastColumn(position))
	{
		--position;
	}	
	
	return position;
}


int Board::generateRandomSwap( int a )
{
	std::array<int, 4> moves;
	moves[0] = a - 1;
	moves[1] = a + 1;
	moves[2] = a - m_columns;
	moves[3] = a + m_columns;
	
	std::uniform_int_distribution<int> distribution(0, 3);

	return moves[distribution(m_generator)];
}

const std::vector<int>& Board::getBoard() const
{
	return m_board;
}

bool Board::trySwap( int a, int b )
{
	bool swapped = false;
	
	if (a == b - 1 && b % m_columns != 0)
	{
		doSwap(a, b);
		swapped = true;
	}
	else if (a == b + 1 && a % m_columns != 0)
	{
		doSwap(a, b);
		swapped = true;
	}
	else if (a == b + m_rows || a == b - m_rows)
	{
		doSwap(a, b);
		swapped = true;
	}
	
	return swapped;
}

void Board::doSwap( int a, int b )
{
	int temp = m_board[a];
	m_board[a] = m_board[b];
	m_board[b] = temp;
}

bool Board::checkPosition( int a, std::vector<int>& matches )
{		
	std::vector<int> tempMatches;
	
	bool hResult = findHorizontalMatches(a, tempMatches);
	
	if (hResult)
	{
		matches.insert(matches.end(), tempMatches.begin(), tempMatches.end());
	}

	tempMatches.clear();

	bool vResult = findVerticalMatches(a, tempMatches);

	if (vResult)
	{
		matches.insert(matches.end(), tempMatches.begin(), tempMatches.end());
	}

	// Add a to matches if we've got something
	bool result = false;

	if (result = vResult || hResult)
	{
		matches.push_back(a);
	}
	else
	{
		matches.clear();
	}

	return result;
}

bool Board::findHorizontalMatches( int a, std::vector<int>& matches )
{
	int matching = 0;
	bool result = false;

	// Look for horizontal matches

	// On the right
	int currentPos = a;

	if (!isLastColumn(a))
	{	
		while(!isFirstColumn(++currentPos) && currentPos < m_board.size())
		{
			if (m_board[currentPos] == m_board[a])
			{
				++matching;
				matches.push_back(currentPos);
			}
			else
			{
				break;
			}
		}
	}

	// On the left
	currentPos = a;

	if (!isFirstColumn(a))
	{
		while(!isLastColumn(--currentPos) && currentPos >= 0)
		{
			if (m_board[currentPos] == m_board[a])
			{
				++matching;
				matches.push_back(currentPos);
			}
			else
			{
				break;
			}
		}
	}
	
	// We need at least two matches, excluding original position
	if (matching >= 2)
	{
		result = true;
	}

	return result;
}

bool Board::findVerticalMatches( int a, std::vector<int>& matches )
{
	bool result = false;

	// Look for vertical matches
	int matching = 0;
	int currentPos = a;

	// Down
	if (!isBottomRow(a))
	{
		while(currentPos < m_board.size() - m_columns)
		{
			currentPos += m_columns;

			if (m_board[currentPos] == m_board[a])
			{
				++matching;
				matches.push_back(currentPos);
			}
			else
			{
				break;
			}
		}
	}

	// Up
	currentPos = a;

	if (!isTopRow(a))
	{
		while(currentPos >= m_columns)
		{
			currentPos -= m_columns;

			if (m_board[currentPos] == m_board[a])
			{
				++matching;
				matches.push_back(currentPos);
			}
			else
			{
				break;
			}
		}
	}
	
	if (matching >= 2)
	{
		result = true;
	}

	return result;
}

bool Board::isTopRow( int a )
{
	return (a <= m_columns);
}

bool Board::isBottomRow( int a )
{
	return (a >= m_columns * (m_rows - 1));
}

bool Board::isFirstColumn( int a )
{
	return (a % m_columns == 0);
}

bool Board::isLastColumn( int a )
{
	return (a % m_columns == m_columns - 1);
}

void Board::removeMatches( const std::vector<int>& matches )
{
	for (auto m : matches)
	{
		m_board[m] = 0;
	}
}






