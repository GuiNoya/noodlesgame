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
        Player p;
        Room *currentRoom;
        Event *showingEvent;
        vector<Room*> rooms;
        vector<Gateway*> gateways;
        vector<Item*> items;
        map<int, Event*> events;
        bool changedRoom;

        void createGame();
        void createEvents();
        void printWelcome();
        void changeRoom(Gateway* gateway);
        Room* transit(Room* origin, Room* dest);
        void performOption(Event::Option* option);

        QTimer* timer;

        inline void createGateway(int id, Room* r1, Room* r2) __attribute__((always_inline));
        inline void drawItems(QPainter& painter, vector<Item*> items);
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
        static const unsigned short DRAW_PER_SECOND = 30;

};

#endif /*ZORKUL_H_*/
