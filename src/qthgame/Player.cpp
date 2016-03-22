#include "Player.h"

Player::Player(string name) : name(name){
}

string Player::getName() {
    return this->name;
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
