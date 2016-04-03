#include <QApplication>
#include "ZorkFlee.h"

int main(int argc, char *argv[]) {
    int currentExitCode = 0;

    do {
        QApplication app(argc, argv);

        ZorkFlee game;
        game.play();

        currentExitCode = app.exec();

    } while (currentExitCode == ZorkFlee::EXIT_CODE_RESTART);

    return currentExitCode;
}
