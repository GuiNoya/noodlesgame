#include "Character.h"

Character::Character(string name, int x, int y, string filename) :
    name(name), rect(x, y, CHARACTER_HEIGHT, CHARACTER_WIDTH), image(ASSET(filename)), moving(false) {
}

string Character::getName() {
    return this->name;
}

QRectF Character::getRect() {
    return rect;
}

QImage& Character::getImage() {
    return image;
}

bool Character::isMoving() {
    return moving;
}

void Character::setPosition(int x, int y) {
    rect.moveTo(x, y);
}

void Character::setPosition(const QPoint point) {
    rect.moveTo(point);
}

void Character::setAnimation(const QPoint dest, double step) {
    direction = (dest - rect.topLeft()) * step;
    this->dest = dest;
    moving = true;
}

bool Character::update() {
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

string Character::toString() {
    return "<Character Name=\"" + name + "\">";
}
