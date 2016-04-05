#ifndef ZORKUL_H_
#define ZORKUL_H_

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
        Room *destRoom = 0;
        Event *showingEvent;
        vector<Room*> rooms;
        vector<Gateway*> gateways;
        map<int, Event*> events;
        map<string, Item*> items;
        const QImage gameLogo;

        bool gameOver = false;

        void createGame();
        void createRooms();
        void createEvents();
        void createItems();
        void printWelcome();
        void changeRoom(Gateway* gateway, string currentRoomPosId, string nextPositionId);
        Room* transit(Room* origin, Room* dest);
        void performOption(Event::Option* option);

        QTimer* timer;

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

#endif /*ZORKUL_H_*/
