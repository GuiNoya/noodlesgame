#include "Character.h"

Character::Character(string name, int x, int y, string filename) :
    name(name), rect(x, y, CHARACTER_HEIGHT, CHARACTER_WIDTH), image(ASSET(filename)), moving(false),
    waiting(false) {
}

// Free the heap memory used by the class
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

// If the Character is not animating, it starts animating, otherwise it will put the animation on the queue
void Character::addAnimation(const QPointF dest, int duration, const function<void()>& c) {
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

// Put the sleep animation on the queue, use a (0, 0) to indicate the sleep animation
void Character::addSleepAnimation(int duration, const function<void()>& c) {
    nextSteps.push(new AnimationStep(QPointF(), duration, c));
}

// Updates the Character position accordingly and return if it is animating
bool Character::update() {
    if (moving) { // If in an animation, updates the position, else return that is an animation
        if (waiting) return false; // If in a sleep animation, does nothing
        QPointF diff = dest - rect.topLeft();
        int x = abs(diff.x());
        int dx = abs(direction.x());
        int y = abs(diff.y());
        int dy = abs(direction.y());
        if (dx >= x && dy >= y) { // If the next movement surpasses the destination point, the animation is finished
            rect.moveTo(dest);
            if (animCallback) animCallback(); // Executes the callback at the end of a normal animation
            if (nextSteps.empty()) { // If there is not a next animation, change the status
                moving = false;
                return true;
            } else { // Else, load the next animation
                AnimationStep* animStep = nextSteps.front();
                nextSteps.pop();
                this->dest = animStep->point;
                if (dest.isNull()) { // If next animation is a sleep animation
                    direction = dest;
                    waiting = true; // Indicate that is waiting
                    QTimer::singleShot(animStep->duration, [&](){ // Set a timer to run the following code when it timestout
                                    waiting = false; // Set the ending of the waiting
                                    if (nextSteps.empty()) {moving = false; return;}
                                    AnimationStep* animStep = nextSteps.front(); // Load next animation
                                    nextSteps.pop();
                                    this->dest = animStep->point;
                                    direction = (dest - rect.topLeft()) * ((float)ANIMATION_DELAY/animStep->duration);
                                    if (animCallback) animCallback(); // Run the callback if exists
                                    animCallback = animStep->callback;
                                    delete animStep;});
                } else { // Else, set the direction to use in a normal animation
                    float step = (float)ANIMATION_DELAY/animStep->duration;
                    direction = (dest - rect.topLeft()) * step;
                }
                animCallback = animStep->callback; // Set the callback
                delete animStep; // Free the space
                return false; // Returns that the animation is still running
            }
        } else { // Else, just updates position
            rect.translate(direction);
            return false;
        }
    }
    return true;
}

string Character::toString() {
    return "<Character Name=\"" + name + "\">";
}
