#include "Gateway.h"

Gateway::Gateway(int id, Room* rooms[2], bool locked=false) : id(id), locked(locked){
    this->rooms[0] = rooms[0];
    this->rooms[1] = rooms[1];
}

string Gateway::toString() {
    return "<item ID=" + id + ", Rooms=" + rooms + ", Locked=" + (locked ? "true>" : "false>");
}

void Gateway::setLocked(bool locked) {
    this->locked = locked;
}

void Gateway::isLocked() {
    return locked;
}

Room* Gateway::getOtherRoom(Room* actualRoom) {
    if (!this->locked) {
        return (actualRoom == rooms[0]) ? rooms[1] : rooms[0];
    }
}
