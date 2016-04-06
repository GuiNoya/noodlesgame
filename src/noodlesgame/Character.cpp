#include "Character.h"

Character::Character(string name, int x, int y, string filename) :
    name(name), rect(x, y, CHARACTER_HEIGHT, CHARACTER_WIDTH), image(ASSET(filename)), moving(false),
    waiting(false) {
}

Character::~Character() {
    while (!nextSteps.empty()) {
        AnimationStep* i = nextSteps.front();
        delete i;
        nextSteps.pop();
    }
}

string Character::getName() const {
    return this->name;
}

QRectF Character::getRect() const {
    return rect;
}

const QImage& Character::getImage() const {
    return image;
}

bool Character::isMoving() const {
    return moving;
}

void Character::setPosition(int x, int y) {
    rect.moveTo(x, y);
}

void Character::setPosition(const QPointF point) {
    rect.moveTo(point);
}

void Character::addAnimation(const QPointF dest, int duration, const function<void()> c) {
    if (!moving) {
        float step = (float)ANIMATION_DELAY/duration;
        direction = (dest - rect.topLeft()) * step;
        this->dest = dest;
        animCallback = c;
        moving = true;
    } else {
        nextSteps.push(new AnimationStep(dest, duration, c));
    }
}

void Character::addSleepAnimation(int duration, const function<void()> c) {
    nextSteps.push(new AnimationStep(QPointF(), duration, c));
}

bool Character::update() {
    if (moving) {
        if (waiting) return false;
        QPointF diff = dest - rect.topLeft();
        int x = abs(diff.x());
        int dx = abs(direction.x());
        int y = abs(diff.y());
        int dy = abs(direction.y());
        if (dx >= x && dy >= y) {
            rect.moveTo(dest);
            if (animCallback) animCallback();
            if (nextSteps.empty()) {
                moving = false;
                return true;
            } else {
                AnimationStep* animStep = nextSteps.front();
                nextSteps.pop();
                this->dest = animStep->point;
                if (dest.isNull()) {
                    direction = dest;
                    waiting = true;
                    QTimer::singleShot(animStep->duration, [&](){
                                    waiting = false;
                                    if (nextSteps.empty()) {moving = false; return;}
                                    AnimationStep* animStep = nextSteps.front();
                                    nextSteps.pop();
                                    this->dest = animStep->point;
                                    direction = (dest - rect.topLeft()) * ((float)ANIMATION_DELAY/animStep->duration);
                                    if (animCallback) animCallback();
                                    animCallback = animStep->callback;
                                    delete animStep;});
                } else {
                    float step = (float)ANIMATION_DELAY/animStep->duration;
                    direction = (dest - rect.topLeft()) * step;
                }
                animCallback = animStep->callback;
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
