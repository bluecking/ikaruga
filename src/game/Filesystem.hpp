/**
 * Filesystem.hpp
 * 
 * @date 29.02.16
 * @author Johan M. von Behren (jvonbehren@uni-osnabrueck.de)
 */
#ifndef SCROLLER_FILESYSTEM_HPP
#define SCROLLER_FILESYSTEM_HPP

#include <string>

using std::string;

namespace jumper
{
    class Filesystem
    {
    public:
        /**
         * Returns the path to the directory where the given file is located (e.g. /user/lib/test.rb -> /user/lib/)
         * with trailing slash
         *
         * @param filePath Path to file where directory path will be extracted
         * @return Path to the directory where the file is located
         */
        static string getDirectoryPath(string filePath);

        /**
         * Returns path to the parent directory from the given directory
         *
         * @param directoryPath Path to the directory from which the parent direcoty path will be extracted
         * @param level Amount of levels to go up in directory
         * @return Path to the parent directory
         */
        static string getParentDirectory(string directoryPath, int level);

        /**
         * Sets the file extension to the given one
         *
         * @param filePath Path to file which extension should be set
         * @param fileExtension File extension to be set
         * @return Path to file with new file extension
         */
        static string setFileExtension(string filePath, string fileExtension);
    };
}


#endif //SCROLLER_FILESYSTEM_HPP
