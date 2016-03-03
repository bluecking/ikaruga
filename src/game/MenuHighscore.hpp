#ifndef MENUHIGHSCORE_H
#define MENUHIGHSCORE_H
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include <list>
#include "MainWindow.hpp"
#include "Profile.hpp"

namespace jumper
{
    class MenuHighscore
    {
    public:
        MenuHighscore(MainWindow* window, Profile *profile);
        void updateHighscore();
        void update(const Uint8*& currentKeyStates, const bool* keyDown);
    private:
        MainWindow* window;
        Profile* profile;
        SDL_Renderer* renderer;
    };
}
#endif // MENUHIGHSCORE_H
