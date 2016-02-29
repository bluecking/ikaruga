#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include "Sound.hpp"

using std::string;

namespace jumper {

    int Sound::NEXT_CHANNEL_ID = -1;
    Sound::Sound(string filename, int type){
        m_channel = NEXT_CHANNEL_ID++;
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
        m_channel = NEXT_CHANNEL_ID++;
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
            Mix_PlayMusic( song, 0);
            Mix_VolumeMusic(volume);
        } else if(m_type == SoundType::SOUND) {
            Mix_HaltChannel(-1);
            Mix_Chunk *sound = Mix_LoadWAV(m_soundFile.c_str());

            if(sound == NULL ){
                std::cout << "Couldnt open " + m_soundFile + "\n";
            }
            Mix_PlayChannel( m_channel, sound, 0 );
            Mix_Volume(m_channel, volume);
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
