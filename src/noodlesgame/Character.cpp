#include "Character.h"

Character::Character(string name, int x, int y, string filename) :
    name(name), rect(x, y, CHARACTER_HEIGHT, CHARACTER_WIDTH), image(ASSET(filename)), moving(false) {
}

Character::~Character() {
    while (!nextSteps.empty()) {
        AnimationStep* i = nextSteps.front();
        delete i;
        nextSteps.pop();
    }
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

void Character::setPosition(const QPointF point) {
    rect.moveTo(point);
}

void Character::addAnimation(const QPointF dest, int duration) {
    if (!moving) {
        float step = (float)ANIMATION_DELAY/duration;
        direction = (dest - rect.topLeft()) * step;
        this->dest = dest;
        moving = true;
    } else {
        nextSteps.push(new AnimationStep(dest, duration));
    }
}

bool Character::update() {
    if (moving) {
        QPointF diff = dest - rect.topLeft();
        int x = abs(diff.x());
        int dx = abs(direction.x());
        int y = abs(diff.y());
        int dy = abs(direction.y());
        if (dx >= x && dy >= y) {
            rect.moveTo(dest);
            if (nextSteps.empty()) {
                moving = false;
                return true;
            } else {
                AnimationStep* animStep = nextSteps.front();
                nextSteps.pop();
                this->dest = animStep->point;
                float step = (float)ANIMATION_DELAY/animStep->duration;
                direction = (dest - rect.topLeft()) * step;
                delete animStep;
                return false;
            }
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
