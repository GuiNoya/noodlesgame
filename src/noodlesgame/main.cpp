#include <QApplication>
#include "ZorkFlee.h"

int main(int argc, char *argv[]) {
    int currentExitCode = 0;

    // Run the aplication
    do {
        QApplication app(argc, argv);

        ZorkFlee game;
        game.play();

        currentExitCode = app.exec();

      // If the currentExitCode is to restart, restart the appplication
    } while (currentExitCode == ZorkFlee::EXIT_CODE_RESTART);

    return currentExitCode;
}
