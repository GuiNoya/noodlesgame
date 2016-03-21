#include <iostream>
#include <stdlib.h>
#include "ZorkUL.h"

using namespace std;

ZorkUL::ZorkUL() {
    createGame();
}

void ZorkUL::createGame() {
    Room *a, *b, *c, *d;

    a = new Room("cell", "You're in a cell. There is a door in front of you.");
    b = new Room("cell room", "You are in the cell room. There is a desk on your side, and a door in front of you.");
    c = new Room("corridor east", "You are in an end of a corridor. There is a plant on your right, with a door beside it, and the cell room on your left.");
    d = new Room("corridor middle", "You are in the middle of the corridor. There is a door in your right and another on your left.");

    rooms.push_back(a);
    rooms.push_back(b);
    rooms.push_back(c);
    rooms.push_back(d);

    Gateway *ab, *bc, *cd;
    ab = new Gateway(0, a, b);
    bc = new Gateway(1, b, c);
    cd = new Gateway(2, c, d);

    gateways.push_back(ab);
    gateways.push_back(bc);
    gateways.push_back(cd);

    currentRoom = a;
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
    if (currentRoom == rooms[0]) {
        o.push_back("Pass through door");
    } else if (currentRoom == rooms[1]) {
        o.push_back("Go to the cell");
        o.push_back("Go through the other door");
    } else if (currentRoom == rooms[2]) {
        o.push_back("Check plant");
        o.push_back("Go back to the cell room");
        o.push_back("Go through the door on your right.");
        o.push_back("Continue in the corridor");
    } else if (currentRoom == rooms[3]) {
        o.push_back("Go to the door on your left");
        o.push_back("Go to the door on your right");
        o.push_back("Go back in the corridor");
    } else {
        o.push_back("Ooops... seems like the game have a problem...");
    }

    return o;
}

void ZorkUL::doAction(int choice) {
    if (currentRoom == rooms[0]) {
        if (choice == 1) {changeRoom(gateways[0]);}
    } else if (currentRoom == rooms[1]) {
        if (choice == 1) {changeRoom(gateways[0]);}
        else if (choice == 2) {changeRoom(gateways[1]);}
    } else if (currentRoom == rooms[2]) {
        if (choice == 1) {cout << "You checked the plant, UHUUUUL!" << endl;}
        else if (choice == 2) {changeRoom(gateways[1]);}
        else if (choice == 3) {cout << "Door is locked." << endl;}
        else if (choice == 4) {changeRoom(gateways[2]);}
    } else if (currentRoom == rooms[3]) {
        if (choice == 1) {cout << "Door is locked." << endl;}
        else if (choice == 2) {cout << "Door is locked." << endl;}
        else if (choice == 3) {changeRoom(gateways[2]);}
    } else {
        cout << "Shit happens..." << endl;
    }
}
