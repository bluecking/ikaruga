#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include "Sound.hpp"

using std::string;

namespace jumper {

    Sound::Sound(string filename, int type, Level &level){
        std::size_t found = level.getPath().find_last_of("/\\");
        string sound_path = level.getPath().substr(0,found);
        found = sound_path.find_last_of("/\\");
        sound_path = sound_path.substr(0,found);
        sound_path += filename;
        m_soundFile = sound_path;
        m_type = type;
        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        {
            printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        }
    }

    void Sound::play(){
        if(m_type == SoundType::SONG && !Mix_PlayingMusic()) {
            Mix_Music* song = Mix_LoadMUS(m_soundFile.c_str());

            if(song == NULL ){
                std::cout << "Couldnt open " + m_soundFile + "\n";
            }
            Mix_PlayMusic( song, 0);
        } else if(m_type == SoundType::SOUND) {
            Mix_HaltChannel(-1);
            Mix_Chunk *sound = Mix_LoadWAV(m_soundFile.c_str());

            if(sound == NULL ){
                std::cout << "Couldnt open " + m_soundFile + "\n";
            }
            Mix_PlayChannel( -1, sound, 0 );
        }
    }

    void Sound::stop(){
        Mix_HaltMusic();
    }

    void Sound::pause(){
        Mix_PausedMusic();
    }

    void Sound::resume() {
        if( Mix_PausedMusic() == 1 )
        {
            Mix_ResumeMusic();
        }
    }
}
