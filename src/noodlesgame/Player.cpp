#include "Player.h"

Player::Player(string name, int x, int y, string filename) : Character(name, x, y, filename) {
}

void Player::setReachedCorner(bool b) {
    reachedCorner = b;
}

bool Player::hasReachedCorner() const {
    return reachedCorner;
}

void Player::addItem(Item *item) {
    inventory.push_back(item);
}

void Player::removeItem(Item *item) {
    FINDREMOVE(inventory, item);
}

bool Player::hasItem(Item *item) {
    for (vector<Item*>::iterator i = inventory.begin(); i != inventory.end(); i++) {
        if ((*i) == item) return true;
    }
    return false;
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
