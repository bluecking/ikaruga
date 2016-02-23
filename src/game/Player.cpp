//
// Created by isaak on 26.11.15.
//


#include "Player.hpp"

#include <iostream>

using std::cout;
using std::endl;

namespace jumper
{
    Player::Player(SDL_Renderer* renderer, std::string filename)
            : Actor(renderer, filename), m_moveDirection(0, 0)
    { }

    Player::Player(SDL_Renderer* renderer, SDL_Texture* texture, int frameWidth, int frameHeight, int numFrames)
            : Actor(renderer, texture, frameWidth, frameHeight, numFrames), m_moveDirection(0, 0)
    { }

    // XXX 2
    void Player::move(Level& level)
    {
        // XXX 3
        nextFrame();
        float dt = getElapsedTime();
        if (dt > 0)
        {
            Vector2f d_move;

            Vector2f test = physics().moveForce();

            d_move = (physics().moveForce() * m_moveDirection * dt);

            // Update velocity
            physics().setVelocity(physics().velocity() + d_move);

            // Damp velocity according to extrinsic level damping
            physics().setVelocity(physics().velocity() * level.physics().damping());

            // Clamp velocities
            if (physics().velocity().x() > physics().maxRunVelocity() * dt)
            {
                physics().setVelocity(Vector2f(physics().maxRunVelocity() * dt,
                                               physics().velocity().y()));
            }

            if (physics().velocity().x() < -physics().maxRunVelocity() * dt)
            {
                physics().setVelocity(Vector2f(-physics().maxRunVelocity() * dt,
                                               physics().velocity().y()));
            }

            if (physics().velocity().y() > physics().maxRunVelocity() * dt)
            {
                physics().setVelocity(Vector2f(physics().velocity().x(), physics().maxRunVelocity() * dt));
            }

            if (physics().velocity().y() < -physics().maxRunVelocity() * dt)
            {
                physics().setVelocity(Vector2f(physics().velocity().x(), -physics().maxRunVelocity() * dt));
            }

            // Set new player position
            physics().setPosition(physics().position() + physics().velocity());

            // Checks if the player moves up or down and updates the source rect
            if(m_moveDirection.y() < 0) {
                if(m_currentTileRow == 0) {
                    m_nextTileRow = 1;
                }

                if(m_currentTileRow == 1){
                    m_nextTileRow = 2;
                }
            }
            else if(m_moveDirection.y() > 0) {
                if(m_currentTileRow == 0) {
                    m_nextTileRow = 3;
                }
                if(m_currentTileRow == 3) {
                    m_nextTileRow = 4;
                }
            }
            else {
                m_nextTileRow = 0;
            }


            /*	// Move camera if player position exceeds window with / 2
            m_camera.position().setX(position().x() - m_levelWidth / 2 + w());
            if(m_camera.position().x() < 0)
            {
                m_camera.position().setX(0);
            }*/

            Collision c = level.resolveCollision(this);
            //cout << c.delta() << endl;
        }

    }

}
