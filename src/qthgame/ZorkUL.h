#ifndef ZORKUL_H_
#define ZORKUL_H_

#include <iostream>
#include <string>
#include "Room.h"
#include "Item.h"

using namespace std;

class ZorkUL {

    private:
        Room *currentRoom;
        vector<Room*> rooms;
        void createRooms();
        void printWelcome();
        void printHelp();
        void goRoom(Command command);
        void createItems();
        void displayItems();

    public:
        ZorkUL();
        void play();
        string go(string direction);

};

#endif /*ZORKUL_H_*/
