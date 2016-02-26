/*
 * ScoreBoard.cpp
 *
 *  Created on: Jan 2, 2016
 *      Author: twiemann
 */

#include "StatusBar.hpp"
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
    SDL_RenderDrawLine(m_renderer,
                       m_startPosition.x(),
                       m_startPosition.y(),
                       m_startPosition.x(),
                       m_startPosition.y()-m_startPosition.y());
    //Buttom line
    SDL_RenderDrawLine(m_renderer,
                       m_endPosition.x(),
                       m_startPosition.y(),
                       m_startPosition.x(),
                       m_startPosition.y());
    //Top line
    SDL_RenderDrawLine(m_renderer,
                       m_endPosition.x(),
                       m_endPosition.y(),
                       m_startPosition.x(),
                       m_endPosition.y());
    //Right line
    SDL_RenderDrawLine(m_renderer,
                       m_endPosition.x(),
                       m_endPosition.y(),
                       m_endPosition.x(),
                       m_startPosition.y());

    //Make the Background black
    SDL_SetRenderDrawColor(m_renderer,0,0,0,1);
	target.w = m_tileWidth;
	target.h = m_tileHeight;
	source.w = target.w;
	source.h = target.h;

    //Render Score
    renderNumber(m_scorePosition, m_score, source, target);

    //Render Weapon
    if(m_weaponChanged){
        m_weaponSource.clear();
        m_weaponTarget.clear();
        setWeaponPosition(Vector2i(m_weaponPosition.x()-((m_weaponName.length()/2)*m_tileWidth),
                                   m_horziontalAlignemnt));
        //Iterate over every character
        for(int i = 0; i < m_weaponName.length(); i++)
        {
            string weaponLetter = string(1, m_weaponName[i]);
            string weaponLetterToUpper = weaponLetter;
            bool upperCase = false;
            int height_offset = 0;
            //check for whitespace
            if(weaponLetter == " ")
            {
                //We don't ever have the 10 as a number, so 10 should be a Whitespace
                source.x = 10 * m_tileWidth;
                source.y = m_numberOffset * m_tileHeight;
            } else {
                //check for casing
                std::transform(weaponLetterToUpper.begin(),
                               weaponLetterToUpper.end(),
                               weaponLetterToUpper.begin(),
                               ::toupper);
                if(weaponLetterToUpper == weaponLetter)
                {
                    upperCase = true;
                    height_offset = m_capitalOffset;
                } else
                {
                    upperCase = false;
                    height_offset = m_minusculeOffset;
                }
                int character_index = 0;
                //calculate letter number in the alphabet, minus 1, because offset
                const char* cha = weaponLetter.c_str();
                if(upperCase)
                {
                    character_index = int(*cha) - 48 - 17;
                } else
                {
                    character_index = int(*cha) - 48 - 23 - m_letterCount;
                }
                source.x = character_index * m_tileWidth;
                source.y = height_offset * m_tileHeight;
            }

            target.x = m_weaponPosition.x() + (i * m_tileWidth) + i;
            target.y = m_weaponPosition.y();

            m_weaponSource.push_back(source);
            m_weaponTarget.push_back(target);

            SDL_RenderCopy(m_renderer, m_texture, &source, &target);
        }
    } else
    {
        for(int i = 0; i < m_weaponSource.size(); i++ )
        {
            SDL_RenderCopy(m_renderer, m_texture, &m_weaponSource.at(i), &m_weaponTarget.at(i));
        }
    }

    //Rendering of the Evolution Stage
    source.x = (std::stoi(m_evolutionStage)-1) * m_tileWidth;
    source.y = m_numberOffset;

    target.x = m_weaponPosition.x() + (m_weaponName.length()*m_tileWidth) + 2*m_tileWidth;
    target.y = m_horziontalAlignemnt;
    SDL_RenderCopy(m_renderer, m_texture, &source, &target);

    //Rendering of Health Display
    renderNumber(m_healthPosition, m_health, source, target);

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
    setHealthPosition(Vector2i(m_endPosition.x() - 10 - 3*m_tileWidth, m_horziontalAlignemnt));
}
void StatusBar::setScorePosition(const Vector2i &position)
{
	m_scorePosition = position;
}

void StatusBar::setWeaponPosition(const Vector2i &position)
{
    m_weaponPosition = position;
}

void StatusBar::setHealthPosition(const Vector2i &position){
    m_healthPosition = position;
}
void StatusBar::setWeaponName(string weaponName)
{
    m_weaponChanged = false;
    if (weaponName != m_weaponName)
    {
        m_weaponChanged = true;
        m_weaponName = weaponName;
    }
}
void StatusBar::setEvolutionStage(string evolutionStage)
{
    m_evolutionStage = evolutionStage;
}

void StatusBar::setHealth(int health)
{
    m_health = health;
}

void StatusBar::renderNumber(Vector2i position, int number, SDL_Rect source, SDL_Rect target)
{
    //SDL_Rect target;
    //SDL_Rect source;

    std::list<int> digits;

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

    int k = 0;
    for(std::list<int>::iterator it = digits.begin(); it != digits.end(); it++)
    {
        int num = *it;
        source.x = num * m_tileWidth;
        source.y = m_numberOffset;


        target.x = position.x() + (k * m_tileWidth) + k;
        target.y = position.y();

        SDL_RenderCopy(m_renderer, m_texture, &source, &target);
        k++;
    }
}

StatusBar::~StatusBar()
{
	// TODO Auto-generated destructor stub
}

} /* namespace jumper */

