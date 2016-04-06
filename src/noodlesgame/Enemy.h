#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"
#include "Room.h"

class Enemy : public Character {
    private:
        bool enemyDown = false;
        bool onRoom4 = false;
        bool onRoom5 = false;
        bool enemyReturn = false;
        map<string, pair<Room*, QPoint>*> positions;

    public:
        Enemy(string name, int x, int y, string filename);
        ~Enemy();
        using Character::setPosition;
        void setEnemyDown(bool b);
        void setEnemyOnRoom4(bool b);
        void setEnemyOnRoom5(bool b);
        void setEnemyReturn(bool b);
        void setPosition(string id);
        void addPosition(string id, Room* room, const QPoint& point);
        QPoint getPosition(string id) const;
        bool isDown() const;
        bool isOnRoom4() const;
        bool isOnRoom5() const;
        bool hasReturned() const;
        string toString() override;
};

#endif // ENEMY_H
