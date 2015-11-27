//
// Created by isaak on 26.11.15.
//

#ifndef JUMPER_PLAYER_H
#define JUMPER_PLAYER_H

#include <string>
#include <SDL.h>
#include "Renderable.hpp"
#include "PhysicPlayer.hpp"
#include <fstream>
#include <iostream>

namespace jumper
{
class Player : public Renderable
{
public:
    Player(SDL_Renderer* renderer, std::string filename);
    void render();
    void move(int direction, int speed);
    void setPosition(Vector2F pos);
    Vector2F position();
    int w() const;
    int h() const;
    int getCurrentAnimation() const;
    PhysicPlayer &physics();

    bool onGround() const;
    void setOnGround(bool m_onGround);
    enum direction {UP, DOWN, LEFT, RIGHT};
    void animate();
    void setJumping(bool jump);
    bool jumping();
    int jumpStart();

    friend std::ostream& operator<< (std::ostream& stream, const jumper::Vector2F& vec);
private:



    int     m_width;
    int     m_height;
    int     m_current_anim;
    int     m_num_anim;
    bool     m_onGround;
    bool     m_jumping;
    int     m_jumpStart;
    PhysicPlayer m_physicalProps;
    SDL_Texture* m_texture;
};

}

#endif //JUMPER_PLAYER_H
