#ifndef ITEMSHOP_H
#define ITEMSHOP_H
#include "MainWindow.hpp"
#include "SDL.h"

class ItemShop
{
    public:
        /**
         * Get the Instance of the shop
         */
        static ItemShop* getShop();
        /**
         * Rendering and handeling pressed keys of ItemShop
         *
         * @param SDL Keystate
         * @param if true then keyDown, else keyUp
         */
        void mainLoop(const Uint8*& currentKeyStates, const bool* keyDown);
        /**
         * Adds money to the shop
         *
         * @param currency count
         */
        static void addMoney(int money);
    private:
        ///shop pointer
        static ItemShop* shop;
        ///constructor
        ItemShop();
        /**
         * pays Money, if something is bought
         *
         * @param currency count
         */
        void payMoney(int money);
        /**
         * load the actual money of the player
         */
        void loadMoney();
        //File where to save, outdated
        std::string sPaymentFile;
        ///renderinstance
        SDL_Renderer* m_renderer;
        ///actual currency count
        long money;
        ///saves actual money to XML
        void saveMoneyToXML();
        /**
         * Buys a specified Weapon
         *
         * @param weaponname
         */
        void buyWeapon(std::string weaponName);
        /**
         * Buys a specified PowerUp
         *
         * @param powerupname
         */
        void buyPowerUp(std::string powerUpName);
};

#endif // ITEMSHOP_H
