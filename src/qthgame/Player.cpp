#include "Player.h"

Player::Player(string name, QRect rect, string filename) : name(name), rect(rect), image(ASSET(filename)){
}

string Player::getName() {
    return this->name;
}

QRect Player::getRect() {
    return rect;
}

QImage& Player::getImage() {
    return image;
}

void Player::addItem(Item *item) {
    inventory.push_back(item);
}

void Player::removeItem(Item *item) {
    for (vector<Item*>::iterator i = inventory.begin(); i != inventory.end(); i++) {
        if ((*i) == item) {
            inventory.erase(i);
        }
    }
}

void Player::update(Room* currentRoom) {
    QRect rr = currentRoom->getRect();
    QPoint pos = currentRoom->getPlayerPosition();
    pos.rx() += rr.left();
    pos.ry() += rr.top();
    rect.setTopLeft(pos);
    rect.setWidth(40);
    rect.setHeight(25);
}

string Player::toString() {
    string s = "<Player Name=\"";
    s += name;
    s += "\" Items=";
    if (inventory.size() > 0 ) {
        for (vector<Item*>::iterator i = inventory.begin(); i != inventory.end(); i++) {
            s += (*i)->toString() + ", ";
        }
        s.erase(s.size()-2, 2);
    } else {
        s += "<>";
    }
    s += ">";
    return s;
}
