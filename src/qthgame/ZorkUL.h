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
        Event::Option* eventIO(string message, Event* event);
        string getMessage();
        Event* getEvent();
        void changeRoom(Gateway* gateway);
        Room* transit(Room* origin, Room* dest);
        void performOption(Event::Option* option);

        QTimer* timer;

        inline void createGateway(int id, Room* r1, Room* r2) __attribute__((always_inline)) { // Could also be a macro
            Gateway* g = new Gateway(id, r1, r2);
            gateways.push_back(g);
            r1->addGateway(g);
            r2->addGateway(g);
        }

        inline void drawItems(QPainter& painter, vector<Item*> items) {
            for (Item* i : items) {
                painter.drawImage(i->getRect(), i->getImage());
            }
        }

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
