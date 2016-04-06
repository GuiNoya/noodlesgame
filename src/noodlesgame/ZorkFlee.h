#ifndef ZORKFLEE_H_
#define ZORKFLEE_H_

#include <iostream>
#include <string>
#include <map>
#include <stdlib.h>

#include <QApplication>
#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include <QTimer>
#include <QPushButton>
#include "Defines.h"

#include "Room.h"
#include "Item.h"
#include "Gateway.h"
#include "Player.h"
#include "Enemy.h"
#include "Event.h"

using namespace std;

class ZorkFlee : public QMainWindow {
    Q_OBJECT

    private:
        Player player;
        Enemy enemy;
        Room *currentRoom;
        Room *destRoom = 0; // Used to correctly draw rooms and at the and of the player's animation
        Event *showingEvent; // Currently displayed event
        vector<Room*> rooms; // Rooms in the game
        vector<Gateway*> gateways; // Gateways in the game
        map<int, Event*> events; // Events in the game
        map<string, Item*> items; // Items in the game
        const QImage gameLogo;
        bool gameOver = false;
        QTimer* timer; // Used to create to main loop

        void createGame();
        void createRooms();
        void createEvents();
        void createItems();
        void changeRoom(Gateway *gateway); // Change room without setting an animation
        // Change room setting an animation to the player (from the currentRoom to the destRoom)
        void changeRoom(Gateway* gateway, string currentRoomPosId, string nextPositionId);
        void performOption(Event::Option* option); // Executes an option and links to the next event; Contains the game logic

        inline void createGateway(int id, Room* r1, Room* r2, bool locked) __attribute__((always_inline));
        inline void runAnimation(Character& character, QPoint nextPosition, int timeMs = 1500);
        inline void drawItems(QPainter& painter, Room *room);
        inline void EVENT(int id, string message, initializer_list<Event::Option*> list);
        inline Event::Option* OPTION(int id, string message);

    protected:
        void paintEvent(QPaintEvent* e) Q_DECL_OVERRIDE;
        void mouseReleaseEvent(QMouseEvent* e) Q_DECL_OVERRIDE;
        void keyPressEvent(QKeyEvent* e) Q_DECL_OVERRIDE;


    public slots:
        void animate();

    public:
        ZorkFlee(QWidget *parent = 0);
        ~ZorkFlee();
        void play();
        static const int EXIT_CODE_RESTART = -7158258;
};

#endif // ZORKFLEE_H
