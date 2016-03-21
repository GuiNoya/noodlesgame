#include <QApplication>
#include "GameWindow.h"
#include "ZorkUL.h"

int main(int argc, char *argv[]) {
    /*QApplication a(argc, argv);
    GameWindow w;
    w.show();

    return a.exec();*/

    ZorkUL game;
    game.play();
    return 0;
}
