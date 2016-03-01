/**
 * Filesystem.cpp
 * 
 * @date 29.02.16
 * @author Johan M. von Behren (jvonbehren@uni-osnabrueck.de)
 */
#include "Filesystem.hpp"

namespace jumper
{
    string Filesystem::getDirectoryPath(string filePath)
    {
        std::size_t found = filePath.find_last_of("/");
        string folderPath = filePath.substr(0, found + 1);
        return folderPath;
    }

    string Filesystem::getParentDirectory(string directoryPath, int level)
    {
        string folderPath = directoryPath;

        for (int i = 0; i < level; i++)
        {
            std::size_t found = folderPath.find_last_of("/");
            folderPath = folderPath.substr(0, found);
            folderPath = getDirectoryPath(folderPath);
        }

        return folderPath;
    }

    string Filesystem::setFileExtension(string filePath, string fileExtension)
    {
        string newFilePath = filePath.substr(0, filePath.find_last_of(".") + 1);
        newFilePath += fileExtension;
        return newFilePath;
    }
}
