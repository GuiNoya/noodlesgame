#ifndef ZORKUL_H_
#define ZORKUL_H_

#include <iostream>
#include <string>
#include "Room.h"
#include "Item.h"
#include "Gateway.h"

using namespace std;

class ZorkUL {

    private:
        Room *currentRoom;
        vector<Room*> rooms;
        vector<Gateway*> gateways;
        void createGame();
        void printWelcome();
        int actionIO(string message, vector<string> options);
        string getMessage();
        vector<string> getOptions(); // create Action, change string to Action
        void doAction(int choice);

        void changeRoom(Gateway* gateway);

    public:
        ZorkUL();
        void play();

};

#endif /*ZORKUL_H_*/
