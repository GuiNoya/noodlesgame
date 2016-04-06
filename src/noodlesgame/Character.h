#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <queue>
#include <functional>
#include <QImage>
#include <QTimer>
#include "Defines.h"

using namespace std;

class Character {
    protected:
        struct AnimationStep {
            const QPointF point;
            const int duration;
            const function<void()> callback;
            AnimationStep(const QPointF p, const int d, const function<void()>& c) : point(p), duration(d), callback(c) {}
        };

        string name;
        QRectF rect;
        QImage image;
        QPointF direction;
        QPointF dest;
        queue<AnimationStep*> nextSteps;
        function<void()> animCallback = 0;
        bool moving;
        bool waiting;
        static const int CHARACTER_HEIGHT = 30;
        static const int CHARACTER_WIDTH = 30;

    public:
        Character(string name, int x, int y, string filename);
        ~Character();
        string getName() const;
        QRectF getRect() const;
        const QImage& getImage() const;
        bool isMoving() const;
        void setPosition(int x, int y);
        void setPosition(const QPointF point);
        void addAnimation(const QPointF dest, int duration, const function<void()>& c=0);
        void addSleepAnimation(int duration, const function<void()>& c=0);
        virtual bool update();
        virtual string toString();
};

#endif // CHARACTER_H
