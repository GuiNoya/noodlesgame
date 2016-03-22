#include <iostream>
#include <stdlib.h>
#include "ZorkUL.h"

#define ROOM(x) rooms[x-1]
#define CORR(x) rooms[7+x]

using namespace std;

ZorkUL::ZorkUL() {
    createGame();
}

void ZorkUL::createGame() {
    Room *r1, *r2, *r3, *r4, *r5, *r6, *r7, *r8;
    Room *c1, *c2, *c3, *c4, *c5, *c6, *c7;

    r1 = new Room("cell", "You're in a cell. There is a door in front of you.");
    r2 = new Room("cell room", "You are in the cell room. There is a desk on your side, and a door in front of you.");
    r3 = new Room("", "");
    r4 = new Room("", "");
    r5 = new Room("", "");
    r6 = new Room("", "");
    r7 = new Room("", "");
    r8 = new Room("", "");
    c1 = new Room("corridor east", "You are in an end of a corridor. There is a plant on your right, with a door beside it, and the cell room on your left.");
    c2 = new Room("corridor middle", "You are in the middle of the corridor. There is a door in your right and another on your left.");
    c3 = new Room("", "");
    c4 = new Room("", "");
    c5 = new Room("", "");
    c6 = new Room("", "");
    c7 = new Room("", "");

    rooms.push_back(r1);
    rooms.push_back(r2);
    rooms.push_back(r3);
    rooms.push_back(r4);
    rooms.push_back(r5);
    rooms.push_back(r6);
    rooms.push_back(r7);
    rooms.push_back(r8);
    rooms.push_back(c1);
    rooms.push_back(c2);
    rooms.push_back(c3);
    rooms.push_back(c4);
    rooms.push_back(c5);
    rooms.push_back(c6);
    rooms.push_back(c7);

    gateways.push_back(new Gateway(0, r1, r2));
    gateways.push_back(new Gateway(1, r2, c1));
    gateways.push_back(new Gateway(2, c1, c2));
    gateways.push_back(new Gateway(3, c2, r3));
    gateways.push_back(new Gateway(4, r3, r8));
    gateways.push_back(new Gateway(5, c2, r4));
    gateways.push_back(new Gateway(6, c2, c3));
    gateways.push_back(new Gateway(7, c3, c4));
    gateways.push_back(new Gateway(8, c4, r6));
    gateways.push_back(new Gateway(9, c4, c5));
    gateways.push_back(new Gateway(10, c5, c6));
    gateways.push_back(new Gateway(11, c6, c7));
    gateways.push_back(new Gateway(12, c6, r7));

    currentRoom = r1;
}

/**
 *  Main play routine.  Loops until end of play.
 */
void ZorkUL::play() {
    printWelcome();

    bool finished = false;
    while (!finished) {
        string m = getMessage();
        vector<string> o = getOptions();
        int action = actionIO(m, o);
        doAction(action);
    }
    cout << endl;
    cout << "end" << endl;
}

void ZorkUL::printWelcome() {
    cout << "start" << endl;
    cout << endl;
    cout << currentRoom->toString() << endl;
}

void ZorkUL::changeRoom(Gateway* gateway) {

    // Try to leave current room.
    Room* nextRoom = gateway->getOtherRoom(currentRoom);

    if (nextRoom == NULL)
        return;
    else {
        currentRoom = nextRoom;
        cout << currentRoom->toString() << endl;
    }
}

int ZorkUL::actionIO(string message, vector<string> options) {
    cout << message << endl;
    for (uint i=0; i < options.size(); i++) {
        cout << i+1 << ". " << options[i] << endl;
    }
    cout << "> ";
    int r;
    cin >> r;
    cout << endl;
    return r;
}

string ZorkUL::getMessage() {
    string m = currentRoom->getDescription();
    return m;
}

vector<string> ZorkUL::getOptions() {
    vector<string> o;
    if (currentRoom == ROOM(1)) {
        o.push_back("Pass through door");
    } else if (currentRoom == ROOM(2)) {
        o.push_back("Go to the cell");
        o.push_back("Go through the other door");
    } else if (currentRoom == CORR(1)) {
        o.push_back("Check plant");
        o.push_back("Go back to the cell room");
        o.push_back("Go through the door on your right.");
        o.push_back("Continue in the corridor");
    } else if (currentRoom == CORR(2)) {
        o.push_back("Go to the door on your left");
        o.push_back("Go to the door on your right");
        o.push_back("Go back in the corridor");
    } else {
        o.push_back("Ooops... seems like the game have a problem...");
    }

    return o;
}

void ZorkUL::doAction(int choice) {
    if (currentRoom == ROOM(1)) {
        if (choice == 1) {changeRoom(gateways[0]);}
    } else if (currentRoom == ROOM(2)) {
        if (choice == 1) {changeRoom(gateways[0]);}
        else if (choice == 2) {changeRoom(gateways[1]);}
    } else if (currentRoom == CORR(1)) {
        if (choice == 1) {cout << "You checked the plant, UHUUUUL!" << endl;}
        else if (choice == 2) {changeRoom(gateways[1]);}
        else if (choice == 3) {cout << "Door is locked." << endl;}
        else if (choice == 4) {changeRoom(gateways[2]);}
    } else if (currentRoom == CORR(2)) {
        if (choice == 1) {cout << "Door is locked." << endl;}
        else if (choice == 2) {cout << "Door is locked." << endl;}
        else if (choice == 3) {changeRoom(gateways[2]);}
    } else {
        cout << "Shit happens..." << endl;
    }
}
