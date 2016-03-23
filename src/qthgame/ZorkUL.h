#ifndef ZORKUL_H_
#define ZORKUL_H_

#include <iostream>
#include <string>
#include "Room.h"
#include "Item.h"
#include "Gateway.h"
#include "Player.h"
#include "Event.h"

using namespace std;

class ZorkUL {

    private:
        Player p;
        Room *currentRoom;
        vector<Room*> rooms;
        vector<Gateway*> gateways;
        vector<Event*> events;
        bool changedRoom;
        void createGame();
        void createEvents();
        void printWelcome();
        Event::Option* eventIO(string message, Event* event);
        string getMessage();
        Event* getEvent();
        void changeRoom(Gateway* gateway);
        void performOption(Event::Option* option);

    public:
        ZorkUL();
        ~ZorkUL();
        void play();

};

#endif /*ZORKUL_H_*/
