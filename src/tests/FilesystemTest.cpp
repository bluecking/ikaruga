/**
 * FilesystemTest.cpp
 * 
 * @date 29.02.16
 * @author Johan M. von Behren (jvonbehren@uni-osnabrueck.de)
 */
#include <string>
#include <iostream>
#include "../game/Filesystem.hpp"

using std::string;
using std::cout;
using std::endl;

void testGetDirectoryPath()
{
    // absolut path
    string path = "/usr/local/Cellar/sdl2/2.0.4/test\\ file\\ name.txt";
    string expected = "/usr/local/Cellar/sdl2/2.0.4/";
    string result = jumper::Filesystem::getDirectoryPath(path);
    cout << (expected.compare(result) == 0 ? "." : "-");

    // relative path
    path = "../sdl2/2.0.4/test\\ file\\ name.txt";
    expected = "../sdl2/2.0.4/";
    result = jumper::Filesystem::getDirectoryPath(path);
    cout << (expected.compare(result) == 0 ? "." : "-");
}

void testGetParentDirectory()
{
    // one level
    string path = "/usr/local/Cellar/sdl2/2.0.4/";
    string expected = "/usr/local/Cellar/sdl2/";
    string result = jumper::Filesystem::getParentDirectory(path, 1);
    cout << (expected.compare(result) == 0 ? "." : "-");

    // two level
    path = "/usr/local/Cellar/sdl2/2.0.4/";
    expected = "/usr/local/Cellar/";
    result = jumper::Filesystem::getParentDirectory(path, 2);
    cout << (expected.compare(result) == 0 ? "." : "-");
}

void testSetFileExtension()
{
    // absolut path
    string path = "/usr/local/Cellar/sdl2/2.0.4/test\\ file\\ name.txt";
    string expected = "/usr/local/Cellar/sdl2/2.0.4/test\\ file\\ name.ti";
    string result = jumper::Filesystem::setFileExtension(path, "ti");
    cout << (expected.compare(result) == 0 ? "." : "-");

    // relative path
    path = "../sdl2/2.0.4/test\\ file\\ name.txt";
    expected = "../sdl2/2.0.4/test\\ file\\ name.ti";
    result = jumper::Filesystem::setFileExtension(path, "ti");
    cout << (expected.compare(result) == 0 ? "." : "-");
}

int main(int arc, char** argv)
{
    testGetDirectoryPath();
    testGetParentDirectory();
    testSetFileExtension();
}
