#ifndef HIGHSCORE_H
#define HIGHSCORE_H
#include <string>
#include "ItemShop.hpp"
#include "Profile.hpp"

namespace jumper{
    /**
     * @brief 	Represents the Highscore of one Level.
     */
    class HighScore
    {
    public:
        /**
         * Creates a Highscore Instance for a level
         *
         * @param profile where the infos have to be set
         * @param name of the unique levelname where the highscore is needed
         */
        HighScore(Profile* profile,std::string levelFile);
        /**
         * Add points to the Highscore of the level
         *
         * @param Count of points
         */
        void addPointsToHighscore(int points);
        /**
         * Saves the Highscore of the level and set them for profile,
         * where the currency is set.
         * Just Call this at the END OF THE LEVEL
         */
        void saveHighscore();
        /**
         * Returns the actual HighScore of the Level
         */
        long getHighscore();
    private:
        //levelfile
        std::string levelFile;
        //actual highscore
        long actualHighscore;
        //profile to manage saving
        Profile* profile;
    };
}

#endif // HIGHSCORE_H
