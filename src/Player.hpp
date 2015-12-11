//
// Created by isaak on 26.11.15.
//

#ifndef JUMPER_PLAYER_H
#define JUMPER_PLAYER_H

#include <fstream>
#include <iostream>
#include <string>

#include <SDL.h>

#include "Actor.hpp"
#include "Vector.hpp"

namespace jumper
{

/***
 * A class to represent an animated sprite controlled
 * by the user.
 */
class Player : public Actor
{
public:

	/***
	 * Constructor.
	 *
	 * @param renderer	A pointer to a valid SDL_Renderer struct that is
	 * 					used for rendering
	 * @param filename	The name of a file with sprite definitions
	 */
	Player(SDL_Renderer* renderer, std::string filename);

	Player(SDL_Renderer* renderer, SDL_Texture* texture, int frameWidth, int frameHeight, int numFrames);

    virtual void move(Level& level);

    /// Prints the player's position to the given stream
    template<typename T>
    friend std::ostream& operator<< (std::ostream& stream, const Vector2<T> & vec);


};

}

#endif //JUMPER_PLAYER_H
