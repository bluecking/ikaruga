#include <ostream>
#include <iostream>
#include "XML.hpp"


int main(int argc, char** argv)
{
    if(argc != 2)
    {
        std::cout << "Please specify a level definition (xml)." << std::endl;
        return -1;
    }

    XML m_xml;
    m_xml.setFilename(argv[1]);
    m_xml.load();

    std::cout << "ID: " << m_xml.getId() << std::endl << "Levelname: " << m_xml.getLevelname() << std::endl;

}