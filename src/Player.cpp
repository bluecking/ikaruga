//
// Created by isaak on 26.11.15.
//


#include "Player.hpp"
namespace jumper
{

Player::Player(SDL_Renderer *renderer, std::string filename)
	: AnimatedRenderable(renderer, filename)
{
	m_jumping = 0;
	m_jumpStart = 0;
	m_physicalProps.setPosition(Vector2f(100, 0));

}

void Player::render()
{
    SDL_Rect target;
    SDL_RendererFlip flip;
    if(m_physicalProps.velocity().x() > 0)
    {
        flip = SDL_FLIP_HORIZONTAL;
    }
    else
    {
        flip = SDL_FLIP_NONE;
    }

    target.x = m_physicalProps.position().x();
    target.y = m_physicalProps.position().y();
    target.w = m_frameWidth;
    target.h = m_frameHeight;

    /* Render current animation frame */
    SDL_RenderCopyEx( getRenderer(), m_texture, &m_sourceRect, &target, 0, NULL, flip);
}

Vector2f Player::position()
{
    return m_physicalProps.position();
}

void Player::move(int direction, int speed)
{
    switch(direction)
    {

        case UP 	:
            m_physicalProps.position()+= Vector2f(0, -speed);   break;
        case DOWN	:
            m_physicalProps.position()+= Vector2f(0, speed);    break;
        case LEFT	:
            m_physicalProps.position()+= Vector2f(-speed, 0);   break;
        case RIGHT  :
            m_physicalProps.position()+= Vector2f(speed, 0);    break;
    }
    nextFrame();
}

void Player::setPosition(Vector2f pos)
{
    m_physicalProps.position() = pos;
}

bool Player::onGround() const
{
    return m_onGround;
}
void Player::setOnGround(bool m_onGround)
{
    Player::m_onGround = m_onGround;
}

PlayerProperty& Player::physics()
{
    return m_physicalProps;
}


bool Player::jumping()
{
    return m_jumping;
}

void Player::setJumping(bool jump)
{
    if(jump) m_jumpStart = m_physicalProps.position().y();
    m_jumping = jump;
}

int Player::jumpStart()
{
    return m_jumpStart;
}
}
