/*
================================
Match.h

Created on: 21 Mar 2014
Author: Jan Holownia

Copyright (c) Jan Holownia <jan.holownia@gmail.com> 2014.

---------------------------------

Description:

Match represents a single game of specified length. This class contains
a timer and holds player's score.
================================
*/

#pragma once

#include <memory>

class Timer;

class Match
{
public:
	Match(void);
	~Match(void);

	void start(unsigned int duration);
	
	void finish();

	void update();

	void updateScore(int matches);
	
	int getScore() const;

	unsigned int timeRemaining() const;

	bool isStarted() const;

	bool isFinished() const;

	static bool getHighScore(int& score);
	
private:
	bool m_started;
	bool m_finished;	
	int m_score;
	unsigned long m_duration;
	std::unique_ptr<Timer> m_timer;

	static bool newHighScore;
	static int highScore;
};

