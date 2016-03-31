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

    public:
        Gateway(int id, Room* room1, Room* room2, bool locked=false);
        string toString();
        void setLocked(bool locked);
        bool isLocked();
        Room* getOtherRoom(Room* currentRoom);

};

#endif // GATEWAY_H
