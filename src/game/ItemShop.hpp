#ifndef ITEMSHOP_H
#define ITEMSHOP_H
#include "MainWindow.hpp"
#include "SDL.h"

class ItemShop
{
    public:
        static ItemShop* getShop();
        void mainLoop(const Uint8*& currentKeyStates, const bool* keyDown);
        static void addMoney(int money);
    private:
        static ItemShop* shop;
        ItemShop();
        void payMoney(int money);
        void loadMoney();
        std::string sPaymentFile;
        SDL_Renderer* m_renderer;
        long money;
        void saveMoneyToXML();
        void buyWeapon(std::string weaponName);
        void buyPowerUp(std::string powerUpName);
};

#endif // ITEMSHOP_H
