/*
 * ScoreBoard.hpp
 *
 *  Created on: Jan 2, 2016
 *      Author: twiemann
 */

#ifndef SRC_SCOREBOARD_HPP_
#define SRC_SCOREBOARD_HPP_

#include "StaticRenderable.hpp"

namespace jumper
{

/**
 * @brief A class to display points using a digit map for rendering
 */
class StatusBar : public StaticRenderable
{
public:


	/**
	 * Constructs a scoreboard for the given renderer
	 *
	 * @param renderer			A valid SDL_Renderer structure
	 * @param texture			A texture that contains the 10 digits (from 0 to 9 in
	 * 							that order)
	 * @param digitWidth		The width of a digit within the texture
	 * @param digitHeight		The height of a digit within the texture
	 */
	StatusBar(SDL_Renderer* renderer, SDL_Texture* texture, int tileWidth, int tileHeight, int capitalOffset, int minusculeOffset, int numberOffset, int letterCount);

	/**
	 * Constructs an empty scoreboard for the renderer
	 *
	 * @param renderer			A valid SDL_Renderer structure
	 */
	StatusBar(SDL_Renderer* renderer);

	/// Sets the displayed score value
	void setScore(int score);

	/// Returns the current score value
	int getScore() const;

	/// Sets the screen position of the scoreboard. The digits are rendered
	/// to the right.
	void setScorePosition(const Vector2i &position);

	/// Renders the scoreboard
	virtual void render();

	/// Destructor
	virtual ~StatusBar();

    void setPosition(const Vector2i &positionStart, const Vector2i &positionEnd);

    void setWeaponPosition(const Vector2i &position);

private:

	/// Current score
	int m_score;

	/// Digit width
	int m_tileWidth;

	/// Digit height
	int m_tileHeight;

	int m_capitalOffset;

	int m_minusculeOffset;

	int m_numberOffset;

    int m_letterCount;

	/// Scoreboard position
	Vector2i m_scorePosition;

	/// Maxim score that can be displayed
	const static int 		m_maxScore;

    Vector2i m_startPosition;
    Vector2i m_endPosition;

    Vector2i m_weaponPosition;
};

} /* namespace jumper */

#endif /* SRC_SCOREBOARD_HPP_ */
