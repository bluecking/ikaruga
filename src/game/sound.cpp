#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include "Sound.hpp"

using std::string;

namespace jumper {

    Sound::Sound(string filename){
        m_soundFile = filename;
        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        {
            printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        }
    }

    void Sound::play(){
        std::cout << "i play something\n";
        const char * test = m_soundFile.c_str();
        Mix_Music* song = Mix_LoadMUS(test);
        //
        //if(song == NULL ){
        //    std::cout << "Couldnt open " + m_soundFile + "\n";
        //}
        //Mix_PlayMusic( song, 0);
    }

    void Sound::stop(){
        std::cout << "i stop something\n";
    }

    void Sound::pause(){
        std::cout << "i pause something\n";
    }

}