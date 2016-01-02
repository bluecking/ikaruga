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

class ScoreBoard : public StaticRenderable
{
public:
	ScoreBoard(SDL_Renderer* renderer, SDL_Texture* texture, int digitWidth, int digitHeight);
	ScoreBoard(SDL_Renderer* renderer);

	void setScore(int score);
	int getScore() const;
	void setPosition(const Vector2i& position);

	virtual void render();
	virtual ~ScoreBoard();

private:
	int 					m_score;
	int						m_digitWidth;
	int						m_digitHeight;
	Vector2i				m_position;
	const static int 		m_maxScore;
};

} /* namespace jumper */

#endif /* SRC_SCOREBOARD_HPP_ */
