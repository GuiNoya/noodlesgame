#ifndef PLAYER_H_
#define PLAYER_H_

#include <cstdlib>
#include <string>
#include <vector>
#include <QRect>
#include <QImage>
#include "Character.h"
#include "Item.h"
#include "Room.h"

using namespace std;

class Player : public Character {

    private:
        vector<Item*> inventory;
        bool reachedCorner = false;

    public:
        Player(string name, int x, int y, string filename);
        void setReachedCorner(bool b);
        bool hasReachedCorner() const;
        void addItem(Item *item);
        void removeItem(Item* item);
        bool hasItem(Item* item);
        string toString() override;

        Player* operator<<(Item* item) {
            inventory.push_back(item);
            return this;
        }

        Player* operator>>(Item* item) {
            FINDREMOVE(inventory, item);
            return this;
        }
};

#endif // PLAYER_H_
