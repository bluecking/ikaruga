/*
 * PuzzleBox.hpp
 *
 *  Created on: Feb 21, 2016
 *      Author: twiemann
 */

#ifndef SRC_GAME_PUZZLEBOX_HPP_
#define SRC_GAME_PUZZLEBOX_HPP_

#include "Item.hpp"

namespace jumper {

    /**
     * @brief A class to represent a puzzle box in the game
     */
    class PuzzleBox : public Item {
    public:

        /**
         * Creates an Item.
         *
         * @param renderer		A SDL-Renderer to render the item
         * @param texture		A SDL-Texture that contains the bitmaps of the frames
         * @param frameWidth	Frame width
         * @param frameHeight	Frame height
         * @param numFrames		Number of frames
         *
         * The sprite, that is displayed after the puzzle box was hit is exspected to
         * be stored after the frames of the initial animation, i.e.,
         * at x = numFrames * frameWidth.
         */
        PuzzleBox(SDL_Renderer *renderer, SDL_Texture *texture, int frameWidth, int frameHeight, int numFrames);

        /// Renders the puzzlebox
        virtual void render();

        //Destructor
        virtual ~PuzzleBox();

        /**
         * Sets the internal hit status to given value
         *
         * @param h true if hit, false if not
         */
        void setHit(bool h) { m_hit = h; }

        /**
         * returns the hit state
         *
         * @returns the hit state - true if hit, false if not
         */
        bool hit() { return m_hit; }

    private:

        /// True if the box was hit by the player (reveals contends)
        bool m_hit;

        //the hit rect
        SDL_Rect m_hitRect;
    };

} /* namespace jumper */

#endif /* SRC_GAME_PUZZLEBOX_HPP_ */
