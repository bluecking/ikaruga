#include "MainWindow.hpp"
#include "Filesystem.hpp"

using namespace jumper;
using std::string;
using std::cout;
using std::endl;


int main(int argc, char** argv)
{
    if (argc != 2)

    {
        std::cout << "Invalid amount of parameters." << std::endl;
        return -1;
    }

    MainWindow window("Ikaruga", 625, 576);
    Game game(&window);
    MainMenu menu(&window, &game, boost::filesystem::path(argv[1]));
    window.setMenu(&menu);

    window.setActualScreen(MainWindow::RENDER_MAINMENU);
    window.run();

    // Free textures
    TextureFactory::instance(window.getRenderer()).deleteAll();
}
