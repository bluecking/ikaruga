/*
 * Sound.hpp
 *
 * @author Jochen Saalfeld (jsaalfeld@uni-osnabrueck.de)
 * @date 29.02.2016
 */

#include "Level.hpp"

#ifndef SCROLLER_SOUND_HPP
#define SCROLLER_SOUND_HPP

using std::string;

namespace jumper
{

    namespace SoundType
    {
        enum SoundType
        {
            SONG,
            SOUND
        };
    }
    //static int NEXT_CHANNEL = 1;
    /**
     * @brief a class to play some fancy wavs
     */
    class Sound
    {

    public:

        /**
         * Standard Constructor
         */
        Sound()
        { };

        /**
         * Constructor to create a sound
         *
         * @param filename a relative path to the base to the soundfile
         * @param type the type of the sound
         */
        Sound(string filename, int type);


        /**
         * Plays the sound
         *
         * @param volume the volume the sound should be played with
         */
        void play(int volume);

        /**
         * Plays the sound with a fadeout
         *
         * @param volume the volume the sound should be played with
         * @param fadeOut the fadeout in ms
         */
        void play(int volume, int fadeOut);

        /**
         * stops Playing
         */
        void stop();

        /**
         * pauses playning
         */
        void pause();

        /**
         * resumes playing
         */
        void resume();

    private:

        //The Filename of the sound
        string m_soundFile;

        //The Type of the Sound
        int m_type;

        int m_channel;
    };
};

#endif //SCROLLER_SOUND_HPP
