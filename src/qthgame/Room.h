#ifndef ROOM_H_
#define ROOM_H_

#include <map>
#include <string>
#include <vector>
#include "Item.h"

using namespace std;

class Room {

    private:
        string name;
        string description;
        map<string, Room*> exits;
        vector<Item> itemsInRoom;
        string exitString();

    public:
        Room(string description);

        // Room related
        void setExits(Room *north, Room *east, Room *south, Room *west);
        Room* nextRoom(string direction);
        string shortDescription();
        string longDescription();

        // Item related
        void addItem(Item *inItem);
        void removeItemFromRoom(int location);
        string displayItem();
        int isItemInRoom(string inString);
        int numberOfItems();

#endif
