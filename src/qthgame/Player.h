#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <cstdlib>
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
        QRectF rect;
        QImage image;
        QPointF direction;
        QPoint dest;
        bool moving;
        static const int PLAYER_HEIGHT = 30;
        static const int PLAYER_WIDTH = 30;

    public:
        Player(string name, int x, int y, string filename);
        string getName();
        QRectF getRect();
        QImage& getImage();
        bool isMoving();
        void setPosition(int x, int y);
        void setPosition(const QPoint point);
        void setAnimation(const QPoint dest, double step);
        void addItem(Item *item);
        void removeItem(Item* item);
        bool hasItem(Item* item);
        bool update();
        string toString();
};

#endif /*CHARACTER_H_*/
