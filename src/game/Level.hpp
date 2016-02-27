/*
 * Level.hpp
 *
 *  Created on: Nov 13, 2015
 *      Author: twiemann
 */

#ifndef SRC_LEVEL_HPP_
#define SRC_LEVEL_HPP_

#include <string>
#include <SDL.h>

#include <vector>
#include "Camera.hpp"
#include "StaticRenderable.hpp"
#include "SparseMatrix.hpp"
#include "Vector.hpp"
#include "WorldProperty.hpp"
#include "Collision.hpp"
#include "TextureFactory.hpp"


namespace jumper {

    enum TilesDirection {
        TUP,
        TDOWN,
        TLEFT,
        TRIGHT
    };

    enum TileType {
        SOLID = 1,
        NONSOLID = 2,
        EDGETOPLEFT = 3,
        EDGETOPRIGHT = 4,
        EDGEDOWNLEFT = 5,
        EDGEDOWNRIGHT = 6
    };

    class Actor;

    /**
     * @brief Represents a level in the jumper game.
     */
    class Level : public StaticRenderable {
    public:

        /**
         * Loads a level from the given .lvl file
         *
         * @param filename
         */
        Level(SDL_Renderer *renderer, std::string filename);

        /**
         * Renders the level to the given renderer
         *
         * @param renderer		A SDL_Renderer to render the tiles
         */
        virtual void render();

        /// Returns the number of tiles in a row
        int levelHeight() const;

        /// Returns the number of tile rows
        int levelWidth() const;

        /// Returns the tile width
        int tileWidth() const;

        /// Returns the tile height
        int tileHeight() const;

        /// Returns the matrix of tiles
        SparseMatrix &tiles();

        /// Returns the physical properties of the level
        WorldProperty &physics();

        /**
         * Destructor
         */
        virtual ~Level();

        /**
         * generetes collision between actor and level
         *
         * @param actor the actor
         */
        Collision resolveCollision(Actor *actor);

        /**
         * moves the actor an the collision
         *
         * @param pos position
         * @param width the heigth
         * @param height the width
         * @param move move to this position
         */
        Vector2f collide(Vector2f pos, int width, int height, Vector2f move);

    private:

        /**
         * Returns the surrounding tiles of the given position
         *
         * @param pos the initial position
         * @param width the width
         * @param height the height
         * @param tiles the surrounding tiles
         */
        void getSurroundingTiles(Vector2f pos, int width, int height, Vector2i *tiles);

        /**
         * Returns the surrounding relevant tiles of the given position
         *
         * @param pos the initial position
         * @param direction the direction of checking
         * @param width the width
         * @param height the height
         * @param tiles the surrounding tiles
         */
        void getSurroundingRelevantTiles(Vector2f pos,
                                         TilesDirection direction,
                                         int width,
                                         int height,
                                         std::vector<Vector2i> *tiles);


        /// Tile width
        int m_tileWidth;

        /// Tile height
        int m_tileHeight;

        /// Offset between the tiles in the tile sheet
        int m_tileOffset;

        /// Number of rows in the tile sheet
        int m_numRows;

        /// Number of tiles per row
        int m_tilesPerRow;

        /// Level width
        int m_levelWidth;

        /// Level height
        int m_levelHeight;

        //the Tiletypes
        std::vector<TileType> m_tileTypes;

        ///Physical properties of level
        WorldProperty m_levelPhysics;

        /// Tile matrix
        SparseMatrix m_tiles;
    };

} /* namespace jumper */

#endif /* SRC_LEVEL_HPP_ */
