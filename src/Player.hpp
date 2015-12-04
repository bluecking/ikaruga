//
// Created by isaak on 26.11.15.
//

#ifndef JUMPER_PLAYER_H
#define JUMPER_PLAYER_H

#include <fstream>
#include <iostream>
#include <string>

#include <SDL.h>

#include "AnimatedRenderable.hpp"
#include "PlayerProperites.hpp"
#include "Vector.hpp"


namespace jumper
{
class Player : public AnimatedRenderable
{
public:

    Player(SDL_Renderer* renderer, std::string filename);
    void render();
    void move(int direction, int speed);
    void setPosition(Vector2f pos);
    Vector2f position();

    PlayerProperties &physics();

    bool onGround() const;
    void setOnGround(bool m_onGround);
    enum direction {UP, DOWN, LEFT, RIGHT};
    void setJumping(bool jump);
    bool jumping();
    int jumpStart();

    template<typename T>
    friend std::ostream& operator<< (std::ostream& stream, const Vector2<T> & vec);
private:

    int     			m_num_anim;
    bool     			m_onGround;
    bool     			m_jumping;
    int     			m_jumpStart;
    PlayerProperties 	m_physicalProps;

};

}

#endif //JUMPER_PLAYER_H
