#include <QApplication>
#include "ZorkUL.h"

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    ZorkUL game;
    game.play();

    return app.exec();
}
