/*
 * Sound.hpp
 *
 * @author Jochen Saalfeld (jsaalfeld@uni-osnabrueck.de)
 * @date 29.02.2016
 */

using std::string;

namespace jumper{

        class Sound {
        public:
            Sound() {};

            Sound(string filename);

            void play();

            void stop();

            void pause();
        private:
            string m_soundFile;

        };
};