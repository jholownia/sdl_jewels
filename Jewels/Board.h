/*
================================
Board.h

Created on: 21 Mar 2014
Author: Jan Holownia

Copyright (c) Jan Holownia <jan.holownia@gmail.com> 2014.

---------------------------------

Description:

This file contains Board class which represents the game board and
encapsulates all algorithms related to generating, matching and removing
the jewels.

================================
*/

#pragma once

#include <vector>
#include <random>

class Board
{
public:
	Board(int rows, int columns);
	~Board(void);

	void init();
	
	void update();
	
	bool trySwap(int a, int b);
	
	void removeMatches(const std::vector<int>& matches);

	bool checkPosition(int a, std::vector<int>& matches);

	const std::vector<int>& getBoard() const;

private:
	const size_t m_rows, m_columns;	
	std::vector<int> m_board;
	std::default_random_engine m_generator;

	
	void reset();
	bool findMatches();
	int generateRandomJewel();
	int generateRandomPosition();
	int generateRandomSwap(int a);
	void doSwap(int a, int b);
	
	bool findHorizontalMatches(int a, std::vector<int>& matches);
	bool findVerticalMatches(int a, std::vector<int>& matches);

	bool isTopRow(int a);
	bool isBottomRow(int a);
	bool isFirstColumn(int a);
	bool isLastColumn(int a);
};

