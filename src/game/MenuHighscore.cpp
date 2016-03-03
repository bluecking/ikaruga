#include "MenuHighscore.hpp"

jumper::MenuHighscore::MenuHighscore(MainWindow* window)
{
    this->window=window;
    this->renderer=window->getRenderer();
}

void jumper::MenuHighscore::update(const Uint8*& currentKeyStates, const bool* keyDown){
    //for(std::list<RenderItem>::iterator iter = renderItems.begin();iter != renderItems.end();iter ++)
    //SDL_RenderCopy(renderer, (*iter).texture, NULL, (*iter).rect);
}

void jumper::MenuHighscore::addText(std::string sMessage){

}
