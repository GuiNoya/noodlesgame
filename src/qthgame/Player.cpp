#include "Player.h"

Player::Player(string name, int x, int y, string filename) :
    name(name), rect(x, y, PLAYER_HEIGHT, PLAYER_WIDTH), image(ASSET(filename)), moving(false) {
}

string Player::getName() {
    return this->name;
}

QRectF Player::getRect() {
    return rect;
}

QImage& Player::getImage() {
    return image;
}

bool Player::isMoving() {
    return moving;
}

void Player::setPosition(int x, int y) {
    rect.moveTo(x, y);
}

void Player::setPosition(const QPoint point) {
    rect.moveTo(point);
}

void Player::setAnimation(const QPoint dest, double step) {
    direction = (dest - rect.topLeft()) * step;
    this->dest = dest;
    moving = true;
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

bool Player::update() {
    if (moving) {
        QPointF diff = dest - rect.topLeft();
        int x = abs(diff.x());
        int dx = abs(direction.x());
        int y = abs(diff.y());
        int dy = abs(direction.y());
        if (dx >= x && dy >= y) {
            moving = false;
            rect.moveTo(dest);
            return true;
        } else {
            rect.translate(direction);
            return false;
        }
    }
    return true;
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
