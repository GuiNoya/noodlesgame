#ifndef GATEWAY_H
#define GATEWAY_H

#include <string>
#include <QRect>
#include "Room.h"

using namespace std;


// Represents a door or passageway
class Gateway {

    private:
        int id;
        Room* rooms[2];
        bool locked;

    public:
        Gateway(int id, Room* room1, Room* room2, bool locked=false);
        string toString();
        void setLocked(bool locked);
        bool isLocked() const;
        Room* getOtherRoom(Room* currentRoom) const;
};

#endif // GATEWAY_H
