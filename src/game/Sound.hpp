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

namespace jumper{

        class Sound {
        public:
            Sound() {};

            Sound(string filename, int type, Level &level);

            void play();

            void stop();

            void pause();

            static const int SONG;

            static const int SOUND;
        private:
            string m_soundFile;

            int m_type;
        };
};

#endif //SCROLLER_SOUND_HPP