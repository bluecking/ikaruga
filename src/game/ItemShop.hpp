#ifndef ITEMSHOP_H
#define ITEMSHOP_H
#include "MainWindow.hpp"
#include "SDL.h"

class ItemShop
{
    public:
        ItemShop();
        void mainLoop(const Uint8*& currentKeyStates, const bool* keyDown);
        static void addMoney(int money);
    private:
        void payMoney(int money);
        void loadMoney();
        std::string sPaymentFile;
        SDL_Renderer* m_renderer;
};

#endif // ITEMSHOP_H
