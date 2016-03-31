#ifndef GATEWAY_H
#define GATEWAY_H

#include <string>
#include <QRect>
#include "Room.h"

using namespace std;

class Gateway {

    private:
        int id;
        Room* rooms[2];
        bool locked;
        //QRect rect;

    public:
        Gateway(int id, Room* room1, Room* room2, /*int x, int y,*/ bool locked=false);
        string toString();
        void setLocked(bool locked);
        bool isLocked();
        Room* getOtherRoom(Room* currentRoom);
        //QRect getRect();

};

#endif // GATEWAY_H
