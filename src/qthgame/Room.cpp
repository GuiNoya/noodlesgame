#include "Room.h"

Room::Room(string name, string description) : name(name), description(description){
}

Room::Room(string name, string description, QRect rect, string filename, int x, int y) :
    name(name), description(description), rect(rect), image(ASSET(filename)), playerPosition(x, y) {
}

string Room::toString() {
    string s = "<Room Name=" + name + ", Description=" + description + ", Items=";
    if (items.size() > 0 ) {
        for (vector<Item*>::iterator i = items.begin(); i != items.end(); i++) {
            s += (*i)->toString() + ", ";
        }
        s.erase(s.size()-2, 2);
    } else {
        s += "<>";
    }
    s += ">";
    return s;
}

// Getters and Setters
string Room::getName() {
    return name;
}

string Room::getDescription() {
    return description;
}

vector<Item*> Room::getItems() {
    return items;
}

vector<Room*> Room::getViewableRooms() {
    return viewableRooms;
}

QRect Room::getRect() {
    return rect;
}

QImage& Room::getImage() {
    return image;
}

QPoint Room::getPlayerPosition() {
    return playerPosition;
}

void Room::setName(string name) {
    this->name = name;
}

void Room::setDescription(string description) {
    this->description = description;
}

void Room::addGateway(Gateway* gateway) {
    this->gateways.push_back(gateway);
}

void Room::addViewableRoom(Room *room) {
    viewableRooms.push_back(room);
}

void Room::addViewableRooms(initializer_list<Room*> rooms) {
    for (auto r : rooms) viewableRooms.push_back(r);
}

// Item related
void Room::addItem(Item *item) {
    if (!isItemInRoom(item)) {
        items.push_back(item);
    }
}

bool Room::removeItem(Item *item) {
    vector<Item*>::iterator i = items.begin();
    while (i != items.end()) {
        if (*i == item) {
            items.erase(i);
            return true;
        }
        i++;
    }
    return false;
}

bool Room::removeItem(int id) {
    vector<Item*>::iterator i = items.begin();
    while (i != items.end()) {
        if ((*i)->getId() == id) {
            items.erase(i);
            return true;
        }
        i++;
    }
    return false;
}

bool Room::isItemInRoom(Item *item) {
    for (int i=items.size()-1; i >= 0; --i) {
        if (items[i] == item) {
            return true;
        }
    }
    return false;
}

bool Room::isItemInRoom(int id) {
    for (int i=items.size()-1; i >= 0; --i) {
        if (items[i]->getId() == id) {
            return true;
        }
    }
    return false;
}

string Room::displayItems() {
    string tempString = "<Items ";
    const int size = items.size();
    for (int i=0; i < size; i++) {
        tempString += i+1;
        tempString += ": ";
        //tempString += items[i]->toString();
        tempString += ", ";
    }
    tempString.erase(tempString.npos-1);
    return tempString;
}

int Room::numberOfItems() {
    return items.size();
}
