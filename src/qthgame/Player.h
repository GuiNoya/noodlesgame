#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <string>
#include <vector>
#include <QRect>
#include <QImage>
#include "Item.h"
#include "Room.h"

using namespace std;

class Player {

    private:
        string name;
        vector<Item*> inventory;
        QRect rect;
        QImage image;

    public:
        Player(string name, QRect rect, string filename);
        string getName();
        QRect getRect();
        QImage& getImage();
        void addItem(Item *item);
        void removeItem(Item* item);
        void update(Room* currentRoom);
        string toString();

};

#endif /*CHARACTER_H_*/
