#include "Enemy.h"

Enemy::Enemy(string name, int x, int y, string filename) : Character(name, x, y, filename) {
}

Enemy::~Enemy() {
    for (auto i : positions) {
        delete i.second;
    }
}

void Enemy::setEnemyDown(bool b) {
    enemyDown = b;
}

void Enemy::setEnemyOnRoom4(bool b) {
    onRoom4 = b;
}

void Enemy::setEnemyOnRoom5(bool b) {
    onRoom5 = b;
}

void Enemy::setEnemyReturn(bool b) {
    enemyReturn = b;
}

void Enemy::setPosition(string id) {
    try {
        pair<Room*, QPoint>* p = positions.at(id);
        QPoint point = p->first->getRect().topLeft();
        point += p->second;
        this->setPosition(point);
    } catch (out_of_range) {
        cerr << "Could not set enemy position to: " << id << endl;
    }
}

void Enemy::addPosition(string id, Room* room, const QPoint& point) {
    if (positions.find(id) != positions.end())
        delete positions[id];
    positions[id] = new pair<Room*, QPoint>(room, point);
}

QPoint Enemy::getPosition(string id) const {
    try {
        pair<Room*, QPoint>* p = positions.at(id);
        QPoint point = p->first->getRect().topLeft();
        point += p->second;
        return point;
    } catch (out_of_range) {
        cerr << "Could not get enemy position: " << id << endl;
    }
    return QPoint();
}

bool Enemy::isDown() const {
    return enemyDown;
}

bool Enemy::isOnRoom4() const {
    return onRoom4;
}

bool Enemy::isOnRoom5() const {
    return onRoom5;
}

bool Enemy::hasReturned() const {
    return enemyReturn;
}

string Enemy::toString() {
    string s = "<Enemy name=\"" + name + "\", isDown=";
    s += enemyDown ? "true" : "false";
    s += ", isOnRoom4=";
    s += onRoom4 ? "true" : "false";
    s += ", isOnRoom5=";
    s += onRoom5 ? "true" : "false";
    s += ", hasReturned=";
    s += enemyReturn ? "true" : "false";
    s += ">";
    return s;
}
