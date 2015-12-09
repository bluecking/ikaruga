#include "MainWindow.hpp"
#include "Level.hpp"

#include <iostream>

using namespace jumper;

int main(int argc, char** argv)
{
	if(argc != 3)
	{
		std::cout << "Please specify a level to render" << std::endl;
		return -1;
	}

	MainWindow window("Jumper", 800, 600);
	Level level(window.getRenderer(), std::string(argv[1]), window.getCam());
	Player player(window.getRenderer(), std::string(argv[2]));

	window.setLevel(&level);
	window.setPlayer(&player);
	window.run();
}
