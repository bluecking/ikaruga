//
// Created by isaak on 26.11.15.
//


#include "Player.hpp"
namespace jumper
{

Player::Player(SDL_Renderer *renderer, std::string filename) : Renderable(renderer)
{
    std::ifstream ifs(filename.c_str());
    std::string textureFileName;
    if(ifs.good())
    {
        ifs >> textureFileName >> m_width >> m_height >> m_num_anim;
        m_texture = loadTexture(textureFileName);
        m_current_anim = 0;
        m_jumping = 0;
        m_jumpStart = 0;
        m_physicalProps.setPosition(Vector2f(100, 0));
    }
    else
    {
        std::cout << "Unable to open file " << filename << std::endl;
    }

}

void Player::render()
{
    SDL_Rect target;
    SDL_Rect source;
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
    target.w = m_width;
    target.h = m_height;

    /* Check animation status */
    if(m_current_anim > m_num_anim)
    {
        m_current_anim = 0;
    }

    /* Determine position of animation frame */
    source.x = m_current_anim * m_width;
    source.y = 0;
    source.w = m_width;
    source.h = m_height;

    /* Render current animation frame */
    SDL_RenderCopyEx( getRenderer(), m_texture, &source, &target, 0, NULL, flip);
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
    m_current_anim++;

    if(m_current_anim >= m_num_anim)
    {
        m_current_anim = 0;
    }
}

void Player::setPosition(Vector2f pos)
{
    m_physicalProps.position() = pos;
}

int Player::w() const
{
    return m_width;
}

int Player::h() const
{
    return m_height;
}

bool Player::onGround() const
{
    return m_onGround;
}
void Player::setOnGround(bool m_onGround)
{
    Player::m_onGround = m_onGround;
}

PhysicPlayer & Player::physics()
{
    return m_physicalProps;
}

void Player::animate()
{
    m_current_anim++;
    if(m_current_anim >= m_num_anim)
    {
        m_current_anim = 0;
    }
}

int Player::getCurrentAnimation() const
{
    return m_current_anim;
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
