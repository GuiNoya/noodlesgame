#include "Enemy.h"

Enemy::Enemy(string name, int x, int y, string filename) : Character(name, x, y, filename) {
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

bool Enemy::isDown() {
    return enemyDown;
}

bool Enemy::isOnRoom4() {
    return onRoom4;
}

bool Enemy::isOnRoom5() {
    return onRoom5;
}

bool Enemy::hasReturned() {
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
