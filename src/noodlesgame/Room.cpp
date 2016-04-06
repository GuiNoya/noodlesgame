#include "Room.h"

Room::Room(string name) : name(name){
}

Room::Room(string name, QRect rect, string filename) :
    name(name), rect(rect), image(ASSET(filename)) {
}

string Room::toString() {
    string s = "<Room Name=" + name + ", Items=";
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
string Room::getName() const {
    return name;
}

vector<Item*> Room::getItems() const {
    return items;
}

vector<Room*> Room::getViewableRooms() const {
    return viewableRooms;
}

QRect Room::getRect() const {
    return rect;
}

const QImage& Room::getImage() const {
    return image;
}

QPoint Room::getPosition(string id) {
    try {
        return positions.at(id) + rect.topLeft();
    } catch (out_of_range) {
        cerr << "Could not get position! Room: " << name << ", Position ID: " << id << endl;
        return rect.topLeft();
    }
}

bool Room::isVisible() const {
    return visible;
}

void Room::setName(string name) {
    this->name = name;
}

void Room::setVisible(bool visible) {
    this->visible = visible;
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

void Room::addPosition(string id, const QPoint& position) {
    positions[id] = position;
}

void Room::addPosition(string id, const int x, const int y) {
    positions[id] = QPoint(x, y);
}

// Item related
void Room::addItem(Item *item) {
    if (!isItemInRoom(item)) {
        items.push_back(item);
    }
}

void Room::removeItem(Item *item) {
    FINDREMOVE(items, item);
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
        tempString += items[i]->toString();
        tempString += ", ";
    }
    tempString.erase(tempString.npos-1);
    return tempString;
}
