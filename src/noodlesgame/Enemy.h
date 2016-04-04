#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"

class Enemy : public Character {
    private:
        bool enemyDown = false;
        bool onRoom4 = false;
        bool onRoom5 = false;
        bool enemyReturn = false;

    public:
        Enemy(string name, int x, int y, string filename);
        void setEnemyDown(bool b);
        void setEnemyOnRoom4(bool b);
        void setEnemyOnRoom5(bool b);
        void setEnemyReturn(bool b);
        bool isDown();
        bool isOnRoom4();
        bool isOnRoom5();
        bool hasReturned();
        string toString() override;
};

#endif // ENEMY_H
