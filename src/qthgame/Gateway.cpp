#include "Gateway.h"

Gateway::Gateway(int id, Room* room1, Room* room2, bool locked/*=false*/)
    : id(id), locked(locked){
    this->rooms[0] = room1;
    this->rooms[1] = room2;
}

string Gateway::toString() {
    string str = "<item ID=";
    str += to_string(id);
    str += ", Rooms=";
    str += rooms[0]->toString();
    str += ", ";
    str += rooms[1]->toString();
    str += ", Locked=";
    str += (locked ? "true>" : "false>");
    return str;
}

void Gateway::setLocked(bool locked) {
    this->locked = locked;
}

bool Gateway::isLocked() {
    return locked;
}

Room* Gateway::getOtherRoom(Room* currentRoom) {
    if (!this->locked) {
        return (currentRoom == rooms[0]) ? rooms[1] : rooms[0];
    }
    return NULL;
}
