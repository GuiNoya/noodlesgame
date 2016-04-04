#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <QImage>
#include "Defines.h"

using namespace std;

class Character {
    protected:
        string name;
        QRectF rect;
        QImage image;
        QPointF direction;
        QPoint dest;
        bool moving;
        static const int CHARACTER_HEIGHT = 30;
        static const int CHARACTER_WIDTH = 30;

    public:
        Character(string name, int x, int y, string filename);
        string getName();
        QRectF getRect();
        QImage& getImage();
        bool isMoving();
        void setPosition(int x, int y);
        void setPosition(const QPoint point);
        void setAnimation(const QPoint dest, double step);
        virtual bool update();
        virtual string toString();
};

#endif // CHARACTER_H
