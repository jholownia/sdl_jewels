/*
================================
Timer.h

Created on: 21 Mar 2014
Author: Jan Holownia

Copyright (c) Jan Holownia <jan.holownia@gmail.com> 2014.

---------------------------------

Description:

A simple timer based around SDL_GetTicks().
================================
*/
#pragma once
class Timer
{
public:
	Timer(void);
	~Timer(void);

	void start();

	void update();

	void reset();

	unsigned int getFrameTime() const;

	unsigned int elapsed() const;

private:
	unsigned int m_starttime;
	unsigned int m_lastFrame;
	unsigned int m_frameTime;
};

