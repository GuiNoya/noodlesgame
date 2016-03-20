#include "Room.h"

Room::Room(string name, string description) : name(name), description(description){
}

string Room::toString() {
    return "<Room Name=" + name + ", Description=" + description + ", Gateways=" + gateways + ", Items=" + items + ">";
}

// Getters and Setters
string Room::getName() {
    return name;
}

string Room::getDescription() {
    return description;
}

void Room::setName(string name) {
    this->name = name;
}

void Room::setDescription(string description) {
    this->description = description;
}

// Room related
void Room::addGateway(Gateway* gateway) {
    for (int i=gateways.size(); i >= 0; --i) {
        if (gateways[i] == gateway) {
            return;
        }
    }
    gateways.push_back(gateway);
}

vector<Gateway*> Room::getGateways() {
    return gateways;
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
        if ((*i)->id == id) {
            items.erase(i);
            return true;
        }
        i++;
    }
    return false;
}

bool Room::isItemInRoom(Item *item) {
    for (int i=items.size(); i >= 0; --i) {
        if (items[i] == item) {
            return true;
        }
    }
    return false;
}

bool Room::isItemInRoom(int id) {
    for (int i=items.size(); i >= 0; --i) {
        if (items[i].getId() == id) {
            return true;
        }
    }
    return false;
}

string Room::displayItems() {
    string tempString = "<Items ";
    const int size = items.size();
    for (i=0; i < size; i++) {
        tempString += i+1;
        tempString += ": ";
        tempString += items[i].toString();
        tempString += ", ";
    }
    tempString.erase(tempString.npos-1);
    return tempString;
}

int Room::numberOfItems() {
    return items.size();
}

