#include "MainWindow.hpp"
#include "Level.hpp"
#include "Bot.hpp"

#include <iostream>

using namespace jumper;

int main(int argc, char** argv)
{
	if(argc != 4)
	{
		std::cout << "Please specify a level to render" << std::endl;
		return -1;
	}

	MainWindow window("Jumper", 800, 600);
	Level level(window.getRenderer(), std::string(argv[1]), window.getCam());
	Player player(window.getRenderer(), std::string(argv[2]));
	Bot bot(window.getRenderer(), std::string(argv[3]));
	bot.physics().setPosition(Vector2f(400, 100));
	bot.physics().setMaxFallVelocity(10);

	window.setLevel(&level);
	window.setBot(&bot);
	window.setPlayer(&player);
	window.run();
}
