#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <queue>
#include <QImage>
#include "Defines.h"

using namespace std;

class Character {
    protected:
        struct AnimationStep {
            const QPointF point;
            const int duration;
            AnimationStep(const QPointF p, const int d) : point(p), duration(d) {}
        };

        string name;
        QRectF rect;
        QImage image;
        QPointF direction;
        QPointF dest;
        queue<AnimationStep*> nextSteps;
        bool moving;
        static const int CHARACTER_HEIGHT = 30;
        static const int CHARACTER_WIDTH = 30;



    public:
        Character(string name, int x, int y, string filename);
        ~Character();
        string getName();
        QRectF getRect();
        QImage& getImage();
        bool isMoving();
        void setPosition(int x, int y);
        void setPosition(const QPointF point);
        void addAnimation(const QPointF dest, int duration);
        virtual bool update();
        virtual string toString();

        //template<typename P, typename D, typename... Params>
        //void setAnimation(Params... parameters);
};

#endif // CHARACTER_H
