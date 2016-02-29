#include "ItemShop.hpp"

ItemShop::ItemShop()
{

}

ItemShop* ItemShop::getShop(){
    if(ItemShop::shop!=NULL)
        return ItemShop::shop;
    ItemShop::shop=new ItemShop();
    return ItemShop::shop;
}

void ItemShop::mainLoop(const Uint8*& currentKeyStates, const bool* keyDown){
    if (currentKeyStates[SDL_SCANCODE_UP])
    {
        //key
    }
    //Clear Renderer
    SDL_RenderClear(m_renderer);

    /*for (size_t i = 0; i < m_renderables.size(); i++)
    {
        m_renderables[i]->render();
    }*/

    // Update screen
    SDL_RenderPresent(m_renderer);
}

void ItemShop::buyWeapon(std::string weaponName){
    //save weapon to XML
}

void ItemShop::buyPowerUp(std::string powerUpName){
    //save PowerUp to XML
}

void ItemShop::payMoney(int money){
    ItemShop::shop->money-=money;
    ItemShop::shop->saveMoneyToXML();
}

void ItemShop::addMoney(int money){
    ItemShop::shop->money+=money;
    ItemShop::shop->saveMoneyToXML();
}

void ItemShop::saveMoneyToXML(){
    //Save Money to XML
}

void ItemShop::loadMoney(){
    //load money from xml
}
