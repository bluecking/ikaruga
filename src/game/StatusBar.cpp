/*
 * ScoreBoard.cpp
 *
 *  Created on: Jan 2, 2016
 *      Author: twiemann
 */

#include "StatusBar.hpp"

#include <iostream>
#include <list>
using std::cout;
using std::endl;
using std::list;

namespace jumper
{

const int StatusBar::m_maxScore = 1000000;


StatusBar::StatusBar(SDL_Renderer* renderer, SDL_Texture* texture, int tileWidth, int tileHeight, int capitalOffset, int minusculeOffset, int numberOffset, int letterCount)
	: StaticRenderable(renderer, texture)
{
	m_score		= 0;
	m_tileWidth = tileWidth;
	m_tileHeight = tileHeight;
    m_capitalOffset = capitalOffset;
    m_minusculeOffset = minusculeOffset;
    m_numberOffset = numberOffset;
    m_letterCount = letterCount;
}

StatusBar::StatusBar(SDL_Renderer* renderer)
	: StaticRenderable(renderer)
{
	m_score = 0;
	m_tileWidth = 0;
	m_tileHeight = 0;

}

void StatusBar::setScore(int score)
{
	if(score < m_maxScore)
	{
		m_score = score;
	}
	else
	{
		m_score = m_maxScore;
	}
}

int StatusBar::getScore() const
{
	return m_score;
}

void StatusBar::render()
{
	SDL_Rect target;
	SDL_Rect source;

	target.w = m_tileWidth;
	target.h = m_tileHeight;
	source.w = target.w;
	source.h = target.h;

	std::list<int> digits;
	int number = m_score;

	if (0 == number)
	{
		digits.push_back(0);
	}
	else
	{
		while (number != 0)
		{
			int last = number % 10;
			digits.push_front(last);
			number = (number - last) / 10;
		}
	}

	int c = 0;
	for(std::list<int>::iterator it = digits.begin(); it != digits.end(); it++)
	{
		int digit = *it;
		source.x = digit * m_tileWidth;
		source.y = 0;

		target.x = m_scorePosition.x() + (c * m_tileWidth) + c;
		target.y = m_scorePosition.y();

		SDL_RenderCopy(m_renderer, m_texture, &source, &target);
		c++;
	}
    for(std::list<int>::iterator it = digits.begin(); it != digits.end(); it++)
    {
        int digit = *it;
        source.x = digit * m_tileWidth;
        source.y = 0;

        target.x = m_weaponPosition.x() + (c * m_tileWidth) + c;
        target.y = m_weaponPosition.y();

        SDL_RenderCopy(m_renderer, m_texture, &source, &target);
        c++;
    }

}
void StatusBar::setPosition(const Vector2i &positionStart, const Vector2i &positionEnd)
{
    m_startPosition = positionStart;
    m_endPosition = positionEnd;
    int startx = m_startPosition.x() + 10;
    int y = (m_startPosition.y()/2) - 3;
    setScorePosition(Vector2i(startx, y));
    //TODO ~ Update Waepon Position, so its always in the middle.
    setWeaponPosition(Vector2i(m_endPosition.x()/2, y));
}
void StatusBar::setScorePosition(const Vector2i &position)
{
	m_scorePosition = position;
}

void StatusBar::setWeaponPosition(const Vector2i &position)
{
    m_weaponPosition = position;
}

StatusBar::~StatusBar()
{
	// TODO Auto-generated destructor stub
}

} /* namespace jumper */

