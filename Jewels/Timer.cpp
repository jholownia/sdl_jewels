/*
================================
Timer.cpp

Created on: 21 Mar 2014
Author: Jan Holownia

Copyright (c) Jan Holownia <jan.holownia@gmail.com> 2014.

---------------------------------

Description:

See the corresponding header file.

================================
*/

#include "Timer.h"
#include <SDL.h>

/*
================
multiply

Return the result of multiplying two integers.
================
*/
Timer::Timer(void)
{
}


Timer::~Timer(void)
{
}

void Timer::start()
{
	m_starttime = SDL_GetTicks();
	m_lastFrame = m_starttime;
}

void Timer::update()
{	
	unsigned int currentTime = SDL_GetTicks();
	m_frameTime = currentTime - m_lastFrame;
	m_lastFrame = currentTime;
}

void Timer::reset()
{
	m_starttime = SDL_GetTicks();
}

unsigned int Timer::getFrameTime() const
{
	return m_frameTime;
}

unsigned int Timer::elapsed() const
{
	return SDL_GetTicks() - m_starttime;
}
