#ifndef GATEWAY_H
#define GATEWAY_H

#include "Room.h"

class Gateway {

    private:
        int id;
        Room* rooms[2];
        bool locked;

    public:
        Gateway(int id, Room* rooms[2], bool locked=false);
        string toString();
        void setLocked(bool locked);
        bool isLocked();
        Room* getOtherRoom(Room* actualRoom);

};

#endif // GATEWAY_H
