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
        static string getDirectoryPath(string filePath);
        static string getParentDirectory(string directoryPath, int level);
    };
}


#endif //SCROLLER_FILESYSTEM_HPP
