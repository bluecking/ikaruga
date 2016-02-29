//
// Created by isaak on 26.11.15.
//


#include "Player.hpp"

using std::cout;
using std::endl;

namespace jumper
{
    Player::Player(SDL_Renderer* renderer, SDL_Texture* texture, int frameWidth, int frameHeight, int numFrames)
            : Actor(renderer, texture, frameWidth, frameHeight, numFrames), m_moveDirection(0, 0)
    { }

    void Player::move(Level& level)
    {
        nextFrame();
        float dt = getElapsedTime();
        if (dt > 0)
        {
            Vector2f d_move;

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

            physics().setVelocity(level.collide(position(), w(), h(), d_move, this));

            // Set new player position
            physics().setPosition(physics().position() + physics().velocity());

            // Checks if the player moves up or down and updates the source rect
            updateMoveAnimation();

            //Collision c = level.resolveCollision(this);
            //cout << c.delta() << endl;
        }

    }

    void Player::shoot()
    {
        // skip if no weapon is set
        if (m_weapon == 0)
        {
            return;
        }

        Vector2f direction(1, 0);
        m_weapon->shoot(direction, position());
    }

    void Player::onCollide()
    {
        std::cout << "CRASH!" << std::endl;

        return;
    }

    void Player::updateMoveAnimation()
    {
        const char NORMAL = 0;
        const char UPHALF = 1;
        const char UPFULL = 2;
        const char DOHALF = 3;
        const char DOFULL = 4;

        // Player moves up
        if (getMoveDirection().y() < 0)
        {
            switch(m_currentTileRow) {
                case NORMAL:     m_nextTileRow = UPHALF; break;
                case DOHALF:     m_nextTileRow = NORMAL; break;
                case DOFULL:     m_nextTileRow = DOHALF; break;
                default:         m_nextTileRow = UPFULL;
            }
        } // Player moves down
        else if (getMoveDirection().y() > 0)
        {
            switch(m_currentTileRow) {
                case NORMAL:     m_nextTileRow = DOHALF; break;
                case UPHALF:     m_nextTileRow = NORMAL; break;
                case UPFULL:     m_nextTileRow = UPHALF; break;
                default:         m_nextTileRow = DOFULL;
            }
        } // Player does not move
        else
        {
            switch(m_currentTileRow) {
                case DOFULL:     m_nextTileRow = DOHALF; break;
                case UPFULL:     m_nextTileRow = UPHALF; break;
                default:         m_nextTileRow = NORMAL;
            }
        }
    }
}
