#ifndef ZORKUL_H_
#define ZORKUL_H_

#include <iostream>
#include <string>
#include <map>
#include <stdlib.h>

#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include <QTimer>
#include "Defines.h"

#include "Room.h"
#include "Item.h"
#include "Gateway.h"
#include "Player.h"
#include "Event.h"

using namespace std;

class ZorkUL : public QMainWindow {
    Q_OBJECT

    private:
        Player player;
        Room *currentRoom;
        Room *destRoom;
        Event *showingEvent;
        vector<Room*> rooms;
        vector<Gateway*> gateways;
        map<int, Event*> events;
        map<string, Item*> items;
        const QImage gameLogo;

        //flags
        bool enemyOnRoom4 = false;
        bool enemyOnRoom5 = false;
        bool hasReachedCorner = false;
        bool gameOver = false;
        bool enemyDown = false;
        bool enemyReturn = false;

        void createGame();
        void createRooms();
        void createEvents();
        void createItems();
        void printWelcome();
        void changeRoom(Gateway* gateway);
        Room* transit(Room* origin, Room* dest);
        void performOption(Event::Option* option);

        QTimer* timer;
        static constexpr double ANIMATION_STEP = 1;
        static const int ANIMATION_DELAY = 100;

        inline void createGateway(int id, Room* r1, Room* r2, bool locked) __attribute__((always_inline));
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
        ZorkUL(QWidget *parent = 0);
        ~ZorkUL();
        void play();
};

#endif /*ZORKUL_H_*/
