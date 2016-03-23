#include <iostream>
#include <stdlib.h>
#include "ZorkUL.h"

#define ROOM(x) rooms[x-1]
#define CORR(x) rooms[7+x]

using namespace std;

ZorkUL::ZorkUL() : p("Main Character"), changedRoom(true) {
    createGame();
}

ZorkUL::~ZorkUL() {
    for (vector<Room*>::iterator i = rooms.begin(); i != rooms.end(); i++) {
        delete (*i);
    }
    for (vector<Gateway*>::iterator i = gateways.begin(); i != gateways.end(); i++) {
        delete (*i);
    }
    for (auto i = events.begin(); i != events.end(); i++) {
        delete (*i);
    }
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

    createEvents();

    currentRoom = r1;
}

void ZorkUL::createEvents() {
    Event *e = new Event("Cela");
    e->addOption(new Event::Option(0, "Pass through door"));
    events.push_back(e);

    e = new Event("Salinha");
    e->addOption(new Event::Option(1, "Go to the cell"));
    e->addOption(new Event::Option(2, "Go through the other door"));
    events.push_back(e);

    e = new Event("Corredor 1");
    e->addOption(new Event::Option(3, "Check the plant"));
    e->addOption(new Event::Option(4, "Go back to the cell room"));
    e->addOption(new Event::Option(5, "Go through the door on your right"));
    e->addOption(new Event::Option(6, "Continue in the corridor"));
    events.push_back(e);

    e = new Event("Corredor 2");
    e->addOption(new Event::Option(7, "Go to the door on your left"));
    e->addOption(new Event::Option(8, "Go to the door on your right"));
    e->addOption(new Event::Option(9, "Go back in the corridor"));
    events.push_back(e);
}

/**
 *  Main play routine.  Loops until end of play.
 */
void ZorkUL::play() {
    printWelcome();

    bool finished = false;
    while (!finished) {
        string m;
        if (changedRoom) {
            m = getMessage();
        } else {
            m = "";
        }
        Event* e = getEvent();
        Event::Option* option = eventIO(m, e);
        changedRoom = false;
        performOption(option);
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

    if (nextRoom != NULL) {
        changedRoom = true;
        currentRoom = nextRoom;
        //cout << currentRoom->toString() << endl;
    }
}

Event::Option* ZorkUL::eventIO(string message, Event* event) {
    if (message != "") {
        cout << message << endl;
    }
    if (event->getMessage() != "") {
        cout << event->getMessage() << endl;
    }
    auto options = event->getOptions();
    for (unsigned int i=0; i < options.size(); i++) {
        cout << i+1 << ". " << options[i]->label << endl;
    }
    cout << "> ";
    int r;
    cin >> r;
    cout << endl;
    return options.at(r-1);
}

string ZorkUL::getMessage() {
    string m = currentRoom->getDescription();
    return m;
}

Event* ZorkUL::getEvent() {
    if (currentRoom == ROOM(1)) {
        return events[0];
    } else if (currentRoom == ROOM(2)) {
        return events[1];
    } else if (currentRoom == CORR(1)) {
        return events[2];
    } else if (currentRoom == CORR(2)) {
        return events[3];
    }
    return NULL;
}

void ZorkUL::performOption(Event::Option* option) {
    switch (option->id) {
        case 0:
            changeRoom(gateways[0]);
            break;
        case 1:
            changeRoom(gateways[0]);
            break;
        case 2:
            changeRoom(gateways[1]);
            break;
        case 3:
            cout << "You checked the plant, UHUUUUL!" << endl;
            p.addItem(new Item(0, "key", "old key"));
            p.addItem(new Item(1, "b key", "old b key"));
            cout << p.toString() << endl;
            break;
        case 4:
            changeRoom(gateways[1]);
            break;
        case 5:
            cout << "Door is locked." << endl;
            break;
        case 6:
            changeRoom(gateways[2]);
            break;
        case 7:
            cout << "Door is locked." << endl;
            break;
        case 8:
            cout << "Door is locked." << endl;
            break;
        case 9:
            changeRoom(gateways[2]);
            break;
        default:
            cout << "Shit happens..." << endl;
            break;
    }
}
