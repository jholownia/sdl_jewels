/*
================================
Match.cpp

Created on: 21 Mar 2014
Author: Jan Holownia

Copyright (c) Jan Holownia <jan.holownia@gmail.com> 2014.

---------------------------------

Description:

See the corresponding header file.

================================
*/

#include "Match.h"
#include "Timer.h"

int Match::highScore = 0;
bool Match::newHighScore = false;

Match::Match(void) :
	m_started(false),
	m_finished(false),
	m_score(0),
	m_duration(0),
	m_timer(new Timer)
{

}


Match::~Match(void)
{

}

void Match::start( unsigned int duration )
{
	m_duration = duration;
	m_timer->start();
	m_started = true;
	m_finished = false;
	m_score = 0;
}

void Match::update()
{
	unsigned int elapsed = m_timer->elapsed() / 1000;

	if (elapsed > m_duration)
	{
		finish();
	}
}

void Match::updateScore( int matches )
{
	m_score += (matches * matches * 10);
}

int Match::getScore() const
{
	return m_score;
}

unsigned int Match::timeRemaining() const
{
	return m_duration - (m_timer->elapsed() / 1000);
}

void Match::finish()
{
	if (m_score > highScore)
	{
		highScore = m_score;
		newHighScore = true;
	}
	else
	{
		newHighScore = false;
	}

	m_started = false;
	m_finished = true;
}

bool Match::getHighScore( int& score )
{
	score = highScore;
	return newHighScore;
}

bool Match::isStarted() const
{
	return m_started;
}

bool Match::isFinished() const
{
	return m_finished;
}


