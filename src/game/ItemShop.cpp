#include "ItemShop.hpp"

ItemShop::ItemShop()
{

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

void ItemShop::payMoney(int money){

}

void ItemShop::loadMoney(){

}

void ItemShop::addMoney(int money){

}
