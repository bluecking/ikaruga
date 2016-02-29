#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include "Sound.hpp"

using std::string;

namespace jumper {

    Sound::Sound(string filename, int type){
        m_soundFile = filename;
        m_type = type;
        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        {
            printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        }
    }
    Sound::Sound(string filename, int type, Level &level){
        string doubleDots = "..";
        std::size_t found;
        found = filename.find_first_of(doubleDots);
        filename = filename.substr(found+doubleDots.length(),filename.length());
        found = level.getPath().find_first_of(doubleDots);
        std::string path = level.getPath().substr(0,found-1);
        found = path.find_last_of("/\\");
        path = path.substr(0,found);
        m_type = type;
        m_soundFile = path + filename;
        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        {
            printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        }
    }

    void Sound::play(int volume){
        if(m_type == SoundType::SONG && !Mix_PlayingMusic()) {
            Mix_Music* song = Mix_LoadMUS(m_soundFile.c_str());

            if(song == NULL ){
                std::cout << "Couldnt open " + m_soundFile + "\n";
            }
            Mix_VolumeMusic(volume);
            Mix_PlayMusic(song, 0);
        } else if(m_type == SoundType::SOUND) {
            Mix_Chunk *sound = Mix_LoadWAV(m_soundFile.c_str());

            if(sound == NULL ){
                std::cout << "Couldnt open " + m_soundFile + "\n";
            }
            Mix_Volume(-1, volume);
            Mix_PlayChannel(-1, sound, 0 );
            Mix_FadeOutChannel(-1,sound->alen/9*10);
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
