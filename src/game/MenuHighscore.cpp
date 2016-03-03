#include "MenuHighscore.hpp"

jumper::MenuHighscore::MenuHighscore(MainWindow* window,Profile* profile)
{
    this->window=window;
    this->renderer=window->getRenderer();
    this->profile=profile;
    this->updateHighscore();
}

void jumper::MenuHighscore::update(const Uint8*& currentKeyStates, const bool* keyDown){
    if (currentKeyStates[SDL_SCANCODE_ESCAPE])
    {
        this->window->setActualScreen(MainWindow::RENDER_MAINMENU);
    }
    SDL_Renderer* renderer=this->window->getRenderer();
    //Clear Renderer
    SDL_RenderClear(renderer);

    //for(std::list<RenderItem>::iterator iter = renderItems.begin();iter != renderItems.end();iter ++)
    //SDL_RenderCopy(renderer, (*iter).texture, NULL, (*iter).rect);

    // Update screen
    SDL_RenderPresent(renderer);
}

void jumper::MenuHighscore::updateHighscore(){
    std::vector<std::pair<std::string,int>> highscores=profile->getHighScores();
    for(int i=0;i<highscores.size();i++){
        std::pair<std::string,int> highscore=highscores.at(i);
        std::cout<<highscore.first<<highscore.second<<std::endl;
    }
}
