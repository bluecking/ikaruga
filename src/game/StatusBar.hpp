/*
 * ScoreBoard.hpp
 *
 *  Created on: Jan 2, 2016
 *      Author: twiemann
 */

#ifndef SRC_SCOREBOARD_HPP_
#define SRC_SCOREBOARD_HPP_


#include <SDL.h>
#include <vector>
#include "FontRender.hpp"

using std::string;

namespace jumper
{

/**
 * @brief A class to display points using a digit map for rendering
 */
class StatusBar : public FontRender
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
	 * @param capitalOffset     The Offset for Capital Letters
	 * @param minusculeOffset   The Offset for lower Case Letters
	 * @param numberOffset      The Offset for numbers
	 * @param letterCount       The numbers of Lettrs
	 * @param offsetMiddle      Offset to get everything perfectly to the midle
	 */
	StatusBar(SDL_Renderer* renderer,
              SDL_Texture* texture,
              int tileWidth,
              int tileHeight,
              int capitalOffset,
              int minusculeOffset,
              int numberOffset,
              int letterCount,
              int offsetMiddle);

    /**
     * Sets the current Score
     *
     * @param score			Sets the Current Score
     */
	void setScore(int score);

    /**
     * Gets the current Score
     *
     * @returns currentScore
     */
	int getScore(void) const;


    /**
     * Renders the Scoreboard
     */
	virtual void render();

    /**
     * Destructor
     */
	virtual ~StatusBar();

    /**
     * Sets the StatusBar Position
     *
     * @param positionStart the lower left corner of the StatusBar
     * @param positionEnd the upper right corner of the StatusBar
     */
    void setPosition(const Vector2i &positionStart, const Vector2i &positionEnd);

    /**
     * Sets the weapon name
     *
     * @param weaponName name of the waepon
     */
    void setWeaponName(string weaponName);

    /**
     * Sets the evolution Stage of the weapon
     *
     * @param evolutionStage evolution Stage of the waepon
     */
    void setEvolutionStage(string evolutionStage);

    /**
     * Sets the health of the Player
     *
     * @param health health of the player
     */
    void setHealth(int health);

private:

    /**
     * Sets the Score Position in the bar
     *
     * @param position the position of the score
     */
    void setScorePosition(const Vector2i &position);

    /**
     * Sets the Weapon Position
     *
     * @param position position of the Weapon String
     */
    void setWeaponPosition(const Vector2i &position);

    /**
     * Sets the Health Position
     *
     * @param position position of the players health
     */
    void setHealthPosition(const Vector2i &position);

	/// Current score
	int m_score;

	/// Digit width
	int m_tileWidth;

	/// Digit height
	int m_tileHeight;

    //Offset for Capital Letters
	int m_capitalOffset;

    //Offset for Minuscule Letters
	int m_minusculeOffset;

    //Offset for NUmbers
	int m_numberOffset;

    //Number of Letters in Tilesheet
    int m_letterCount;

    //Number to get it exaclty in the middle of the statusbar
    int m_offsetMiddle;

    //y-Axis so its in the middle of the Statusbar
    int m_horziontalAlignemnt;

    //WeaponName
    string m_weaponName;

    //look, if the weapon changed
    bool m_weaponChanged;

    //EvolutionStage
    string m_evolutionStage;


    //the Weapon Source in the tilesheet
    std::vector<SDL_Rect> m_weaponSource;

    //the Weapon Target in the Window
    std::vector<SDL_Rect> m_weaponTarget;

	/// Scoreboard position
	Vector2i m_scorePosition;

	/// Maxim score that can be displayed
	const static int 		m_maxScore;

    //lower left corner of the StatusBar
    Vector2i m_startPosition;

    //upper Right corner of the Statusbar
    Vector2i m_endPosition;

    //Position of the weapon String
    Vector2i m_weaponPosition;

    //Poistion of the Players Health
    Vector2i m_healthPosition;

    //Players Health
    int m_health;

    void displayNumber(int number, Vector2i position, SDL_Rect source, SDL_Rect target);
};

} /* namespace jumper */

#endif /* SRC_SCOREBOARD_HPP_ */
