/*
 * ScoreBoard.cpp
 *
 *  Created on: Jan 2, 2016
 *      Author: twiemann
 */

#include "StatusBar.hpp"
#include <SDL.h>
#include <iostream>
#include <list>
using std::cout;
using std::endl;
using std::list;
using std::string;

namespace jumper
{

const int StatusBar::m_maxScore = 1000000;


StatusBar::StatusBar(SDL_Renderer* renderer,
                     SDL_Texture* texture,
                     int tileWidth,
                     int tileHeight,
                     int capitalOffset,
                     int minusculeOffset,
                     int numberOffset,
                     int letterCount,
                     int offsetMiddle)
	: StaticRenderable(renderer, texture)
{
	m_score		= 0;
	m_tileWidth = tileWidth;
	m_tileHeight = tileHeight;
    m_capitalOffset = capitalOffset;
    m_minusculeOffset = minusculeOffset;
    m_numberOffset = numberOffset;
    m_letterCount = letterCount;
    m_offsetMiddle = offsetMiddle;
    m_weaponChanged = false;
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


    //Paint the Border in Red
    SDL_SetRenderDrawColor(m_renderer,255,0,0,1);
    //left line
    SDL_RenderDrawLine(m_renderer, m_startPosition.x(), m_startPosition.y(), m_startPosition.x(), m_startPosition.y()-m_startPosition.y());
    //Buttom line
    SDL_RenderDrawLine(m_renderer, m_endPosition.x(), m_startPosition.y(), m_startPosition.x(), m_startPosition.y());
    //Top line
    SDL_RenderDrawLine(m_renderer, m_endPosition.x(), m_endPosition.y(), m_startPosition.x(), m_endPosition.y());
    //Right line
    SDL_RenderDrawLine(m_renderer, m_endPosition.x(), m_endPosition.y(), m_endPosition.x(), m_startPosition.y());

    //Make the Background black
    SDL_SetRenderDrawColor(m_renderer,0,0,0,1);
	target.w = m_tileWidth;
	target.h = m_tileHeight;
	source.w = target.w;
	source.h = target.h;

    //Render Score
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

    //Render Weapon
    if(m_weaponChanged)
    {
        std::cout << m_weaponName;
    }
    //std::list<int> capitals;

    /*
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
    */

}
void StatusBar::setPosition(const Vector2i &positionStart, const Vector2i &positionEnd)
{
    m_startPosition = positionStart;
    m_endPosition = positionEnd;
    //to get the vertical alignment straight, we need to substract our tileheight from the middle of our statusbar
    //and substract to offset to get it perfectly horizontally aligned
    m_horziontalAlignemnt = (m_startPosition.y()/2) - ((m_tileHeight/2)-m_offsetMiddle);
    setScorePosition(Vector2i(m_startPosition.x() + 10, m_horziontalAlignemnt));
    //TODO ~ Update Weapon Position, so its always in the middle.
    setWeaponPosition(Vector2i(m_endPosition.x()/2, m_horziontalAlignemnt));
}
void StatusBar::setScorePosition(const Vector2i &position)
{
	m_scorePosition = position;
}

void StatusBar::setWeaponPosition(const Vector2i &position)
{
    m_weaponPosition = position;
}

void StatusBar::setWeaponName(string weaponName)
{
    m_weaponChanged = false;
    if (weaponName != m_weaponName)
    {
        m_weaponChanged = true;
        m_weaponName = weaponName;
    }
    //cout << weaponName + "\n";
}

StatusBar::~StatusBar()
{
	// TODO Auto-generated destructor stub
}

} /* namespace jumper */

