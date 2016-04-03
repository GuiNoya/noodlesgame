#include <QApplication>
#include "ZorkUL.h"

int main(int argc, char *argv[]) {
    int currentExitCode = 0;

    do {
        QApplication app(argc, argv);

        ZorkUL game;
        game.play();

        currentExitCode = app.exec();

    } while (currentExitCode == ZorkUL::EXIT_CODE_RESTART);

    return currentExitCode;
}
